#include "Game.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <random>
#include <chrono>
#include <thread>


Game::Game(const std::string& config)
{
	Game::init(config);
}

void Game::init(const std::string& path)
{

	bool previousKeyState_Enter = false;
	bool previousKeyState_P = false;

	m_keyState.emplace("Enter", previousKeyState_Enter);
	m_keyState.emplace("P", previousKeyState_P);

	// 创建一个哈希表string-case, 来指明读取的是哪个配置
	std::unordered_map<std::string, int> stringSwitch;
	stringSwitch["Window"] = 1;
	stringSwitch["Font"] = 2;
	stringSwitch["Player"] = 3;
	stringSwitch["Enemy"] = 4;
	stringSwitch["Bullet"] = 5;

	// 读取配置文件内容
	std::ifstream file("config.txt");
	if (!file)
	{
		std::cerr << "无法打开文件。" << std::endl;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string key;
		iss >> key;
		switch (stringSwitch[key])
		{
			case 1:
			{
				iss >> m_windowConfig.W >> m_windowConfig.H >> m_windowConfig.FL >> m_windowConfig.FS;
			} break;

			case 2:
			{
				iss >> m_fontConfig.FF >> m_fontConfig.FS >> m_fontConfig.OR >> m_fontConfig.OG >> m_fontConfig.OB;
			} break;
			
			case 3:
			{
				iss >> m_playerConfig.SR
					>>m_playerConfig.CR
					>> m_playerConfig.S
					>> m_playerConfig.FR
					>> m_playerConfig.FG
					>> m_playerConfig.FB
					>> m_playerConfig.OR
					>> m_playerConfig.OG
					>> m_playerConfig.OB
					>> m_playerConfig.OT
					>> m_playerConfig.V;
			} break;
			
			case 4:
			{
				iss >> m_enemyConfig.SR
					>> m_enemyConfig.CR
					>> m_enemyConfig.SMIN
					>> m_enemyConfig.SMAX
					>> m_enemyConfig.OR
					>> m_enemyConfig.OG
					>> m_enemyConfig.OB
					>> m_enemyConfig.OT
					>> m_enemyConfig.VMIN
					>> m_enemyConfig.VMAX
					>> m_enemyConfig.L
					>> m_enemyConfig.SP;

			} break;
		
			case 5:
			{
				iss >> m_bulletConfig.SR
					>> m_bulletConfig.CR
					>> m_bulletConfig.S
					>> m_bulletConfig.FR
					>> m_bulletConfig.FG
					>> m_bulletConfig.FB
					>> m_bulletConfig.OR
					>> m_bulletConfig.OG
					>> m_bulletConfig.OB
					>> m_bulletConfig.OT
					>> m_bulletConfig.V
					>> m_bulletConfig.L;

			} break;
		}
	}
	file.close();

	m_window.setFramerateLimit(m_windowConfig.FL);
	if (m_windowConfig.FS)
	{
		m_window.create(sf::VideoMode::getFullscreenModes()[0], "ShootGame", sf::Style::Fullscreen);
	}
	else
	{
		m_window.create(sf::VideoMode(m_windowConfig.W, m_windowConfig.H), "ShootGame");
	}

	// 加载字体配置，设置文本显示样式
	m_font.loadFromFile(m_fontConfig.FF);
	std::string score = "Score: " + std::string(" ") +  std::to_string(m_score);
	m_text.setString(score);
	m_text.setCharacterSize(m_fontConfig.FS);
	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color(m_fontConfig.OR, m_fontConfig.OG, m_fontConfig.OB));
	m_text.setPosition(16, 10);
	
	sf::FloatRect textRect = m_text.getLocalBounds();
	//std::cout << " m_text.getOrigin().x: " << m_text.getOrigin().x << " m_text.getOrigin().y: " << m_text.getOrigin().x << std::endl;
	//std::cout << " textRect.left: " << textRect.left << " textRect.top" << textRect.top << std::endl;

	m_text.setOrigin(textRect.left, textRect.top);

	spawnPlayer();

}

void Game::setPaused(bool paused)
{
	m_paused = paused;
}

void Game::run()
{
	while (m_running)
	{

		if (!m_paused)
		{
			m_entities.update();
			sEnemySpawner();
			sMovement();
			sCollision();
		}
		sUserInput();
		sRender();
		m_currentFrame++;
	}
}

void Game::spawnPlayer()
{
	auto entity = m_entities.addEntity("player");
	entity->cShape = std::make_shared<CShape>(
		m_playerConfig.SR,
		m_playerConfig.V,
		sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB),
		sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB),
		m_playerConfig.OT);

	entity->cTransform = std::make_shared<CTransform>(sf::Vector2f(m_windowConfig.W / 2.0f, m_windowConfig.H / 2.0f), CVec2f(m_playerConfig.S, m_playerConfig.S), .0f);
	entity->cInput = std::make_shared<CInput>();
	entity->cCollision = std::make_shared<CCollision>(m_playerConfig.CR);
	entity->cLifespan = std::make_shared<CLifespan>(100);
	m_player = entity;
}

void Game::spawnEnemy()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// 边数，几边形
	std::uniform_int_distribution<int> dis_vertex(m_enemyConfig.VMIN, m_enemyConfig.VMAX);
	int randomVertex = dis_vertex(gen);
	//std::cout << "Random number in range [" << m_enemyConfig.VMIN << ", " << m_enemyConfig.VMAX << "]: " << randomVertex << std::endl;

	// 速度
	std::uniform_real_distribution <float> dis_velocity(m_enemyConfig.SMIN, m_enemyConfig.SMAX);
	float randomVelocity = dis_velocity(gen);
	//std::cout << "Random number in range [" << m_enemyConfig.SMIN << ", " << m_enemyConfig.SMAX << "]: " << randomVelocity<< std::endl;

	// 位置
	std::uniform_real_distribution<float> dis_pos_w(m_enemyConfig.CR * 1.0f, m_windowConfig.W - m_enemyConfig.CR);
	float randomPos_w = dis_pos_w(gen);
	if (randomPos_w > m_player->cTransform->pos.x - m_player->cShape->circle.getRadius())
	{
		randomPos_w -= m_player->cShape->circle.getRadius();
	}
	if (randomPos_w < m_player->cTransform->pos.x + m_player->cShape->circle.getRadius())
	{
		randomPos_w -= m_player->cShape->circle.getRadius();
	}
	std::uniform_real_distribution<float> dis_pos_h(m_enemyConfig.CR * 1.0f, m_windowConfig.H - m_enemyConfig.CR);
	float randomPos_h = dis_pos_h(gen);
	if (randomPos_h > m_player->cTransform->pos.y - m_player->cShape->circle.getRadius())
	{
		randomPos_h -= m_player->cShape->circle.getRadius();
	}
	if (randomPos_h < m_player->cTransform->pos.y + m_player->cShape->circle.getRadius())
	{
		randomPos_h -= m_player->cShape->circle.getRadius();
	}

	// 颜色
	std::uniform_int_distribution<int> dis_r(0, m_enemyConfig.OR);
	std::uniform_int_distribution<int> dis_g(0, m_enemyConfig.OG);
	std::uniform_int_distribution<int> dis_b(0, m_enemyConfig.OB);
	int randomR = dis_r(gen);
	int randomG = dis_g(gen);
	int randomB = dis_b(gen);

	//std::cout << "Random width in range [" << m_enemyConfig.CR * 1.0f << ", " << m_windowConfig.W - m_enemyConfig.CR << "]: " << randomPos_w << "  ";
	//std::cout << "Random height in range [" << m_enemyConfig.CR * 1.0f << ", " << m_windowConfig.H- m_enemyConfig.CR << "]: " << randomPos_h << std::endl;
	float px = m_player->cTransform->pos.x;
	float py = m_player->cTransform->pos.y;

	float delta_x = px - randomPos_w;
	float delta_y = py - randomPos_h;

	float angle = std::atanf(delta_y / delta_x);
	float sine = std::abs(sinf(angle));
	float cosine = std::abs(cosf(angle));
	float vx, vy;
	if (delta_x > 0)
	{
		vx = randomVelocity * cosine;;
	}
	else
	{
		vx = -randomVelocity * cosine;
	}
	if (delta_y > 0)
	{
		vy = randomVelocity * sine;
	}
	else
	{
		vy = -randomVelocity * sine;
	}

	auto entity = m_entities.addEntity("enemy");
	entity->cShape = std::make_shared<CShape>(
		m_enemyConfig.SR,
		randomVertex,
		sf::Color(randomR, randomG, randomB),
		sf::Color(randomR, randomG, randomB),
		m_enemyConfig.OT);
	entity->cTransform = std::make_shared<CTransform>(sf::Vector2f(randomPos_w, randomPos_h), CVec2f(vx, vy), .0f);
	entity->cLifespan = std::make_shared<CLifespan>(m_enemyConfig.L);
	entity->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR);
	entity->cScore = std::make_shared<CScore>(10 * randomVertex);

	m_lastEnemySpawnTime = m_currentFrame;

}

void Game::spawnSmallEnemies(const std::shared_ptr<Entity>& entity)
{
	//std::cout << "spawnSmall Entity" << std::endl;
	// 获取entity的形状，几个边就生成几个小多边形
	int vertex = entity->cShape->points;
	float angle = 360.0 / vertex;
	//std::cout << angle << std::endl;

	for (auto i = 0; i < vertex; ++i)
	{
		//std::cout << std::cosf(i * angle) << std::endl;
		//std::cout << std::sinf(i * angle) << std::endl;
		//std::cout << entity->cShape->radius * std::sinf(i * angle) << std::endl;
		//std::cout << entity->cShape->radius * std::sinf(i * angle) << std::endl;

		float cosine = std::cosf(i * angle);
		float sine = std::sinf(i * angle);
		float x = entity->cTransform->pos.x + entity->cShape->radius * cosine;
		float y = entity->cTransform->pos.y + entity->cShape->radius * sine;
		
		auto e = m_entities.addEntity("smallEnemy");

		//std::cout << "x: " << x << "y: " << y << std::endl;
		e->cShape = std::make_shared<CShape>(
			entity->cShape->radius / 2,
			vertex,
			entity->cShape->circle.getFillColor(),
			entity->cShape->circle.getOutlineColor(),
			m_playerConfig.OT / vertex);

		float vx = entity->cTransform->velocity.x / 2;
		float vy = entity->cTransform->velocity.y / 2;

		e->cTransform = std::make_shared<CTransform>(sf::Vector2f(x, y), CVec2f(vx * cosine, vy * sine), .0f);
		e->cLifespan = std::make_shared<CLifespan>(5);
	}
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const CVec2f& target)
{

	float px = m_player->cTransform->pos.x;
	float py = m_player->cTransform->pos.y;

	float delta_x = px - target.x;
	float delta_y = py - target.y;

	float radian = atanf(delta_y / delta_x);
	float sine = std::abs(sinf(radian));
	float cosine = std::abs(cosf(radian));

	float bullet_pos_x, bullet_pos_y;

	float vx = 0, vy = 0;
	float x = m_player->cShape->circle.getRadius() * std::cosf(radian);
	float y = m_player->cShape->circle.getRadius() * std::sinf(radian);


	if (delta_x < 0)
	{
		bullet_pos_x = m_player->cTransform->pos.x + x + 4;
		vx = m_bulletConfig.S * cosine;

	}

	else if (std::abs(delta_x) < 1e-6)
		bullet_pos_x = m_player->cTransform->pos.x;
	else
	{
		bullet_pos_x = m_player->cTransform->pos.x - x - 4;
		vx = -m_bulletConfig.S * cosine;
	}


	if (delta_y < 0)
	{
		vy = m_bulletConfig.S * sine;
		bullet_pos_y = m_player->cTransform->pos.y + y + 4;
	}

	else if (std::abs(delta_y) < 1e-6)
		bullet_pos_y = m_player->cTransform->pos.y;
	else
	{
		vy = -m_bulletConfig.S * sine;
		bullet_pos_y = m_player->cTransform->pos.y - y - 4;
	}




	auto e = m_entities.addEntity("bullet");
	e->cShape = std::make_shared<CShape>(
		m_bulletConfig.SR,
		m_bulletConfig.V,
		sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB),
		sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB),
		m_bulletConfig.OT);
	e->cTransform = std::make_shared<CTransform>(sf::Vector2f(bullet_pos_x, bullet_pos_y), CVec2f(vx, vy), .0f);
	e->cLifespan = std::make_shared<CLifespan>(m_bulletConfig.L);
	e->cCollision = std::make_shared<CCollision>(m_bulletConfig.CR);
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{

}

// Systems to do
void Game::sEnemySpawner()
{
	if (m_currentFrame - m_lastEnemySpawnTime > m_enemyConfig.SP * 60)
		spawnEnemy();
}

void Game::sMovement()
{
	if (m_player->cInput->up ||
		m_player->cInput->down ||
		m_player->cInput->left ||
		m_player->cInput->right)
	{
		if (m_player->cInput->up)
		{
			m_player->cTransform->velocity.y = -std::abs(m_player->cTransform->velocity.y);
			m_player->cTransform->pos.y += m_player->cTransform->velocity.y / 30.0f;
		}

		if (m_player->cInput->down)
		{
			m_player->cTransform->velocity.y = std::abs(m_player->cTransform->velocity.y);
			m_player->cTransform->pos.y += m_player->cTransform->velocity.y / 30.0f;
		}

		if (m_player->cInput->left)
		{
			m_player->cTransform->velocity.x = -std::abs(m_player->cTransform->velocity.x);
			m_player->cTransform->pos.x += m_player->cTransform->velocity.x / 30.0f;
		}
		if (m_player->cInput->right)
		{
			m_player->cTransform->velocity.x = std::abs(m_player->cTransform->velocity.x);
			m_player->cTransform->pos.x += m_player->cTransform->velocity.x / 30.0f;
		}

		if (m_player->cTransform->pos.x - m_player->cShape->radius < 0)
			m_player->cTransform->pos.x = m_player->cShape->radius;
		if (m_player->cTransform->pos.x + m_player->cShape->radius > m_windowConfig.W)
			m_player->cTransform->pos.x = m_windowConfig.W - m_player->cShape->radius;

		if (m_player->cTransform->pos.y - m_player->cShape->radius < 0)
			m_player->cTransform->pos.y = m_player->cShape->radius;
		if (m_player->cTransform->pos.y + m_player->cShape->radius > m_windowConfig.H)
			m_player->cTransform->pos.y = m_windowConfig.H - m_player->cShape->radius;
	}
	else
	{
		m_player->cTransform->pos.x += 0;
		m_player->cTransform->pos.y += 0;
	}
	
	for (auto e : m_entities.getEntities("bullet"))
	{
		e->cTransform->pos.x += e->cTransform->velocity.x / (5 * 60.0f - 30.0f);
		e->cTransform->pos.y += e->cTransform->velocity.y / (5 * 60.0f - 30.0f);

	}

	for (auto e : m_entities.getEntities("enemy"))
	{
		e->cTransform->pos.x += e->cTransform->velocity.x / 120.0f;
		e->cTransform->pos.y += e->cTransform->velocity.y / 120.0f;
	}

	for (auto e : m_entities.getEntities("smallEnemy"))
	{
		e->cTransform->pos.x += e->cTransform->velocity.x / 60.0f;
		e->cTransform->pos.y += e->cTransform->velocity.y / 60.0f;
	}

	for (auto e : m_entities.getEntities())
	{
		if (e->cTransform->pos.x < 0 ||
			e->cTransform->pos.x > m_windowConfig.W ||
			e->cTransform->pos.y < 0 ||
			e->cTransform->pos.y > m_windowConfig.H)
		{
			e->cLifespan->remaining = 0;
		}

		else
		{
			/*e->cLifespan->remaining--;*/
		}
	}
}

void Game::sCollision()
{
	for (auto& bullet : m_entities.getEntities("bullet"))
	{
		for (auto& enemy : m_entities.getEntities("enemy"))
		{
			float distance = CVec2f(bullet->cTransform->pos.x,
				bullet->cTransform->pos.y).dist(CVec2f(enemy->cTransform->pos.x,
					enemy->cTransform->pos.y));
			if (distance <= std::pow((bullet->cCollision->radius + enemy->cCollision->radius), 2))
			{
				//std::cout << "collision" << std::endl;

				bullet->cLifespan->remaining = 0;
				enemy->cLifespan->remaining = 0;
				m_score += enemy->cScore->score;

				spawnSmallEnemies(enemy);


			}
		}
	}

	for (auto& enemy : m_entities.getEntities("enemy"))
	{
		float distance = CVec2f(enemy->cTransform->pos.x,
			enemy->cTransform->pos.y).dist(CVec2f(m_player->cTransform->pos.x,
				m_player->cTransform->pos.y));
		if (distance <= std::pow((enemy->cCollision->radius + m_player->cCollision->radius), 2))
		{
			m_player->cLifespan->remaining -= enemy->cScore->score / 10 * 2;
			enemy->cLifespan->remaining = 0;
		}
	}
	
	//std::cout << "total: " << m_player->cLifespan->total << " remaining: " << m_player->cLifespan->remaining << std::endl;
}

void Game::sUserInput()
{

	sf::Event event;

	while (m_window.pollEvent(event))
	{
			if (event.type == sf::Event::Closed)
			{
				m_running = false;
			}

			// input the enter to restart the game

			if (m_over)
			{
				bool currentKeyState = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
				if (currentKeyState && !m_keyState["Enter"])
				{
					m_over = false;
					m_paused = false;
					
					m_window.clear();
					spawnPlayer();
					
				}
				m_keyState["Enter"] = currentKeyState;
			}
			

			// input p to pause the game
			bool currentKeyState = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
			if (currentKeyState && !m_keyState["P"])
			{
				if (!m_paused)
				{
					m_paused = true;
					// draw the end scene

				}

				else
					m_paused = false;
			}
			m_keyState["P"] = currentKeyState;

			// get the keyboard input
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W:
				{
					//std::cout << "W pressed" << std::endl;
					m_player->cInput->up = true;
				} break;

				case sf::Keyboard::S:
				{
					//std::cout << "S pressed" << std::endl;
					m_player->cInput->down = true;
				} break;

				case sf::Keyboard::A:
				{
					//std::cout << "A pressed" << std::endl;
					m_player->cInput->left = true;
				} break;

				case sf::Keyboard::D:
				{
					//std::cout << "D pressed" << std::endl;
					m_player->cInput->right = true;
				} break;

				default: break;
				}
			}

			if (event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W:
				{
					//std::cout << "W released" << std::endl;
					m_player->cInput->up = false;
				} break;

				case sf::Keyboard::S:
				{
					//std::cout << "S released" << std::endl;
					m_player->cInput->down = false;
				} break;

				case sf::Keyboard::A:
				{
					//std::cout << "A released" << std::endl;
					m_player->cInput->left = false;
				} break;

				case sf::Keyboard::D:
				{
					//std::cout << "D released" << std::endl;
					m_player->cInput->right = false;
				} break;

				default: break;
				}
			}

		// get the mouse input

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (!m_paused)
					{
						spawnBullet(m_player, CVec2f((float)event.mouseButton.x, (float)event.mouseButton.y));

					}


				}

				if (event.mouseButton.button == sf::Mouse::Right)
				{
					//float bullet_pos_x, bullet_pos_y;
					//float delta_x = m_player->cTransform->pos.x - (float)event.mouseButton.x;
					//float delta_y = m_player->cTransform->pos.y - (float)event.mouseButton.y;
					////std::cout << delta_x << "  " << delta_y << std::endl;
					//float radian = std::atanf(std::abs(delta_y / delta_x));
					////std::cout << std::cosf(radian) << "  ";
					////std::cout << std::sinf(radian) << std::endl;
					//float x = m_player->cShape->radius * std::cosf(radian);
					//float y = m_player->cShape->radius * std::sinf(radian);

					////std::cout << x << "  " << y << std::endl;
					////float x = delta_x;
					////float y = delta_y;

					//if (delta_x < 0)
					//	bullet_pos_x = m_player->cTransform->pos.x + x + 2;
					//else if (std::abs(delta_x) < 1e-6)
					//	bullet_pos_x = m_player->cTransform->pos.x;
					//else
					//	bullet_pos_x = m_player->cTransform->pos.x - x - 2;

					//if (delta_y < 0)
					//	bullet_pos_y = m_player->cTransform->pos.y + y + 2;
					//else if (std::abs(delta_y) < 1e-6)
					//	bullet_pos_y = m_player->cTransform->pos.y;
					//else
					//	bullet_pos_y = m_player->cTransform->pos.y - y - 2;

					//float delta_bullet_angle = 30.0f;
					//float delta_bullet_x = m_player->cShape->radius * std::cosf(radian - 30.0f);
					//float delta_bullet_y = m_player->cShape->radius * std::sinf(radian - 30.0f);

					//spawnBullet(m_player, CVec2f(bullet_pos_x, bullet_pos_y), radian);
					//spawnBullet(m_player, CVec2f(bullet_pos_x + delta_bullet_x, bullet_pos_y + delta_bullet_y), radian - 30.0f);
					//spawnBullet(m_player, CVec2f(bullet_pos_x + delta_bullet_x, bullet_pos_y + delta_bullet_y), radian + 30.0f);
				}
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{

			}
	}

}

void Game::sRender()
{
	m_window.clear();


	if (m_player->cLifespan->remaining > 0)
	{
		sf::Text paused_text;
		if (m_paused)
		{
			paused_text.setString("PAUSED! Please tap 'P' to start the game!");
			paused_text.setFont(m_font);
			paused_text.setCharacterSize(36);

			sf::FloatRect textRect = paused_text.getLocalBounds();
			//std::cout << " textRect.left: " << textRect.left << " textRect.right" << textRect.top << std::endl;
			paused_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			paused_text.setPosition(m_window.getSize().x / 2.0f, 200);

			paused_text.setFillColor(sf::Color(103, 125, 106));
		}

		m_player->cTransform->angle += 5;
		m_player->cShape->circle.setPosition(m_player->cTransform->pos);
		m_player->cShape->circle.setRotation(m_player->cTransform->angle);

		//m_window.draw(m_player->cShape->circle);

		for (auto& e : m_entities.getEntities("enemy"))
		{
			if (m_currentFrame % 360 == 0)
			{
				m_player->cTransform->angle += 2;
				e->cShape->circle.setRotation(m_player->cTransform->angle);

			}

		}

		for (auto& e : m_entities.getEntities("smallEnemy"))
		{
			if (m_currentFrame % 240 == 0)
			{
				--e->cLifespan->remaining;
			}

			if (m_currentFrame % 120 == 0)
			{
				m_player->cTransform->angle += 2;
				e->cShape->circle.setRotation(m_player->cTransform->angle);

			}
			//std::cout<< "smallEntity" << std::endl;
		}

		for (auto& e : m_entities.getEntities())
		{
			sf::Color currentColor = e->cShape->circle.getFillColor();
			sf::Color newColor(currentColor.r, currentColor.g, currentColor.b,
				255 * e->cLifespan->remaining / e->cLifespan->total);
			e->cShape->circle.setFillColor(newColor);

			e->cShape->circle.setPosition(e->cTransform->pos);
			m_window.draw(e->cShape->circle);
		}
		
		if (m_paused)
		{
			m_window.draw(paused_text);
		}

		std::string score = "Score:" + std::to_string(m_score);
		m_text.setString(score);
		m_window.draw(m_text);

	}

	else
	{
		// game over, clear all stuff
		for (auto& e : m_entities.getEntities())
		{
			e->cLifespan->remaining = 0;
		}
		m_entities.update();
		m_score = 0;
		// draw the end scene
		sf::Text end_text;
		end_text.setString("GameOver!");
		end_text.setFont(m_font);
		end_text.setCharacterSize(120);
		
		sf::FloatRect textRect = end_text.getLocalBounds();
		//std::cout << " textRect.left: " << textRect.left << " textRect.right" << textRect.top << std::endl;
		end_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		end_text.setPosition(m_window.getSize().x / 2.0f, m_window.getSize().y / 2.0f);

		end_text.setFillColor(sf::Color(255, 138, 138));

		m_window.draw(end_text);

		m_paused = true;
		m_over = true;
		
	}




	//std::cout << m_player->cTransform->pos.x << "  " << m_player->cTransform->pos.y << std::endl;
	//std::cout << m_player->cShape->circle.getPosition().x << "  " << m_player->cShape->circle.getPosition().y << std::endl;

	m_window.display();

}

