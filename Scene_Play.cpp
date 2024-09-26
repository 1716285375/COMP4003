#include <iostream>
#include <fstream>

#include "SFML/Window/Event.hpp"
//#include "Scene_Menu.h"
#include "Scene_Play.h"
#include "Assets.h"
 #include "Physics.h"
#include "GameEngine.h"
#include "Components.h"
#include "Action.h"
#include "SFML/Graphics/RectangleShape.hpp"



Scene_Play::Scene_Play(GameEngine* gameEngine, const std::string& levelPath)
	: Scene(gameEngine), m_levelPath(levelPath) {
	init(levelPath);
}

void Scene_Play::init(const std::string& levelPath) {
	m_actionMap.clear();

	registerAction(sf::Keyboard::P, "PAUSE");
	registerAction(sf::Keyboard::Escape, "QUIT");
	registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");   // Toggle drawing (T)extures
	registerAction(sf::Keyboard::C, "TOGGLE_COLLISION"); // Toggle drawing (C)ollision Boxes
	registerAction(sf::Keyboard::G, "TOGGLE_GRID");      // Toggle drawing (G)rid

	// TODO: Register all other gameplay Actions
	// registerAction(sf::Keyboard::W, "JUMP");
	registerAction(sf::Keyboard::Escape, "BACK");

	registerAction(sf::Keyboard::W, "JUMP");
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::A, "LEFT");
	registerAction(sf::Keyboard::D, "RIGHT");
	registerAction(sf::Keyboard::Space, "SHOOT");

	m_gridText.setCharacterSize(12);
	m_gridText.setFont(m_game->assets().getFont("Mario"));
	// m_gridText.setFont(m_game->assets().getFont("Tech"));

	loadLevel(levelPath);
}

vec2 Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity) {
	// TODO: This function takes in a grid (x,y) position and an Entity
	//       Return a vec2 indicating where the CENTER position of the Entity should be
	//       You must use the Entity's Animation size to position it correctly
	//       The size of the grid width and height is stored in m_gridSize.x and m_gridSize.y
	//       The bottom-left corner of the Animation should aligh with the bottom left of the grid cell

	auto entitySize = entity->getComponent<CAnimation>().animation.getSize();
	std::cout << entity->getComponent<CAnimation>().animation.getName() << ": " << gridX * m_gridSize.x + entitySize.x / 2.0f << " " << gridY * m_gridSize.y + entitySize.y / 2.0f << std::endl;
	return vec2(gridX * m_gridSize.x + entitySize.x / 2.0f, gridY * m_gridSize.y + entitySize.y / 2.0f);
}

void Scene_Play::loadLevel(const std::string& fileName) {
	// reset the entity manager every time we load a level
	m_entityManager = EntityManager();


	// TODO: read in the level file and add the appropriate entities
	//       use the PlayerConfig struct m_playerConfig to store player properties
	//       this struct is defined at the top of Scene_Play.h

	std::ifstream file(fileName);
	if (!file)
	{
		std::cerr << "Could not load " << fileName << " file\n";
		exit(-1);
	}

	std::string assetType;
	while (file >> assetType)
	{
		std::string name;
		float x, y;
		file >> name >> x >> y;

		auto e = m_entityManager.addEntity(assetType);
		


		if (assetType == "water")
		{

		}

		else if (assetType == "sling")
		{

		}
		else if (assetType == "pipe")
		{

		}
		else if (assetType == "ground")
		{

		}
		else if (assetType == "stair")
		{

		}
		else if (assetType == "dec")
		{

		}
		else if (assetType == "obstacle")
		{

		}
		else if (assetType == "stuff")
		{

		}

		e->addComponent<CAnimation>(m_game->assets().getAnimation(name), false);

		e->addComponent<CTransform>(gridToMidPixel(x, y, e));
	}

	// NOTE: all the code below is sample code which shows you how to
	//       set up and use entities with the new syntax, it should be removed

	spawnPlayer();

	//// some sample entities
	//auto brick = m_entityManager.addEntity("tile");
	//// IMPORTANT: always add the CAnimation component first so that gridToMidPixel can compute correctly
	//brick->addComponent<CAnimation>(m_game->assets().getAnimation("Brick"), true);
	//brick->addComponent<CTransform>(vec2(96, 480));
	//// NOTE: Your final code should position the entity with the grid x,y position read from the file:
	//// brick->addComponent<CTransform>(gridToMidPixel(gridX, gridY, brick));

	//if (brick->getComponent<CAnimation>().animation.getName() == "Brick") {
	//	//std::cout << "This could be a good way of identifying if a tile is a brick!\n";
	//}

	//auto block = m_entityManager.addEntity("tile");
	//// block->addComponent<CAnimation>(m_game->assets().getAnimation("Block"), true);
	//block->addComponent<CAnimation>(m_game->assets().getAnimation("Ground"), true);
	//block->addComponent<CTransform>(vec2(224, 480));
	//// add a bounding box, this will now show up if we press the 'C' key
	//// block->addComponent<CBoundingBox>(m_game->assets().getAnimation("Block").getSize());
	//block->addComponent<CBoundingBox>(m_game->assets().getAnimation("Ground").getSize());

	//auto question = m_entityManager.addEntity("tile");
	//question->addComponent<CAnimation>(m_game->assets().getAnimation("Ground"), true);
	//question->addComponent<CTransform>(vec2(352, 480));

	// NOTE: THIS IS INCREDIBLY IMPORTANT PLEASE READ THIS EXAMPLE
	//       Components are now returned as references rather than pointers
	//       If you do not specify a reference variable type, it will COPY the component
	//       Here is an example:
	//
	//       This will COPY the transform into the variable 'transform1' - it is INCORRECT
	//       Any changes you make to transform1 will not be changed inside the entity
	//       auto transform1 = entity->get<CTransform>()
	//
	//       This will REFERENCE the transform with the variable 'transform2' - it is CORRECT
	//       Now any changes you make to transform2 will be changed inside the entity
	//       auto& transform2 = entity->get<CTransform>()
}

void Scene_Play::spawnPlayer() {
	// here is a sample player entity which you can use to construct other entities

	//m_player = m_entityManager.addEntity("player");
	//m_player->addComponent<CAnimation>(m_game->assets().getAnimation("Stand"), true);
	//m_player->addComponent<CTransform>(
	//	gridToMidPixel(m_playerConfig.X, m_playerConfig.Y, m_player),
	//	vec2(m_playerConfig.SPEED, 0),
	//	vec2(-1.0, 1.0),
	//	0);
	//m_player->addComponent<CBoundingBox>(vec2(m_playerConfig.CX, m_playerConfig.CY));

	////std::cout << " pos: x: " << m_player->getComponent<CTransform>().pos.x << " "
	////	<< m_player->getComponent<CTransform>().pos.y << std::endl;

	//// TODO: be sure to add the remaining components to the player

	//m_player->addComponent<CInput>();
	//m_player->addComponent<CGravity>(m_playerConfig.GRAVITY);
	//m_player->addComponent<CState>("Stand");
}

void Scene_Play::spawnBullet(std::shared_ptr<Entity> entity) {
	// TODO: this should spawn a bullet at the given entity, going in the direction the entity is facing
	// 
	//auto bullet = m_entityManager.addEntity("bullet");
	//bullet->addComponent<CAnimation>(m_game->assets().getAnimation(m_playerConfig.WEAPON), true);

	//float dir = 1.0f;
	//float gravity = 0.5;
	//if (entity->getComponent<CTransform>().scale.x > 0)
	//{
	//	dir = -1.0f;
	//	gravity = -0.5;
	//}
	//	
	//bullet->addComponent<CTransform>(
	//	entity->getComponent<CTransform>().pos,
	//	vec2(dir * 2 * m_playerConfig.SPEED, 0),
	//	entity->getComponent<CTransform>().scale,
	//	0
	//);
	////bullet->addComponent<CGravity>(gravity);
	//bullet->addComponent<CLifespan>(90, m_currentFrame);
	//bullet->addComponent<CBoundingBox>(bullet->getComponent<CAnimation>().animation.getSize());
}	

void Scene_Play::update() {
	m_entityManager.update();

	// TODO: implement pause functionality

	sMovement();
	sLifespan();
	sCollision();
	sAnimation();
	sRender();
	 m_currentFrame++;
	 //std::cout << m_currentFrame << std::endl;
}

void Scene_Play::sMovement() {
	// TODO: Implement player movement/jumping based on its CInput component
	// TODO: Implement gravity's effect on the player
	// TODO: Implement the maximum player speed in both X and Y directions
	// NOTE: Setting an entity's scale.x to -1/1 will make it face to the left/right
	//auto& p_trans = m_player->getComponent<CTransform>();
	//auto& input = m_player->getComponent<CInput>();

	//p_trans.velocity.x = 0;
	////p_trans.velocity.y = 0;
	////std::cout << m_player->getComponent<CTransform>().velocity.y << std::endl;

	//if (input.left)
	//{
	//	p_trans.velocity.x = -m_playerConfig.SPEED;

	//	if (p_trans.scale.x < 0)
	//		p_trans.scale.x = 1;
	//}
	//else if (input.right)
	//{
	//	p_trans.velocity.x = m_playerConfig.SPEED;
	//	if (p_trans.scale.x > 0)
	//		p_trans.scale.x = -1;
	//}

	//if (input.up)
	//{
	//	if (input.canJump)
	//	{
	//		//std::cout << input.up << std::endl;
	//		input.canJump = false;
	//		p_trans.velocity.y = -m_playerConfig.JUMP;
	//		
	//	}
	//}

	////

	//if (input.shoot)
	//{
	//	if (input.canShoot)
	//	{
	//		spawnBullet(m_player);
	//		input.canShoot = false;
	//	}
	//}
	//else
	//	input.canShoot = true;

	//for (const auto& e : m_entityManager.getEntities())
	//{
	//	if (e->hasComponent<CGravity>())
	//	{
	//		vec2& v = e->getComponent<CTransform>().velocity;
	//		v.y += e->getComponent<CGravity>().gravity;
	//		if (v.y > m_playerConfig.MAX_SPEED)
	//			v.y = m_playerConfig.MAX_SPEED;
	//	}
	//	e->getComponent<CTransform>().prevPos = e->getComponent<CTransform>().pos;
	//	e->getComponent<CTransform>().pos += e->getComponent<CTransform>().velocity;
	//}
	//std::cout << m_player->getComponent<CTransform>().velocity.y << std::endl;

}

void Scene_Play::sLifespan() {
	// TODO: Check lifespan of entities the have them, and destroy them if the go over

	//for (const auto& e : m_entityManager.getEntities())
	//{
	//	if (e->hasComponent<CLifespan>())
	//	{

	//		auto& eLife = e->getComponent<CLifespan>();
	//		if (m_currentFrame - eLife.frameCreated >= eLife.lifespan)
	//		{
	//			e->destroy();
	//		}
	//	}
	//}

	//	// control bullet quantity, be spawned every 10 frames
	//for (const auto& entity : m_entityManager.getEntities("bullet")) {
	//	auto& bulletLife = entity->getComponent<CLifespan>();
	//	if (m_currentFrame - bulletLife.frameCreated == 30) {
	//		m_player->getComponent<CInput>().canShoot = true;
	//	}
	//}
}

void Scene_Play::sCollision() {
	// REMEMBER: SFML's (0,0) position is in the TOP-LEFT corner
	//           This means jumping will have a negative y-component
	//           and gravity will have a positive y-component
	//           Also, something BELOW something else will hava a y value GREATER than it
	//           Also, something ABOVE something else will hava a y value LESS than it

	// TODO: Implement Physics::GetOverlap() function, use it inside this function

	// TODO: Implement bullet/tile collisions
	//       Destroy the tile if it has a Brick animation
	// TODO: Implement player/tile collisions and resolutions
	//       Update the CState component of the player to store whether
	//       it is currently on the ground or in the air. This will be
	//       used by the Animation system
	// TODO: Check to see if the player has fallen down a hole (y > height())
	// TODO: Don't let the player walk off the left side of the map
	//for (const auto& bullet : m_entityManager.getEntities("bullet"))
	//{
	//	for (const auto& tile : m_entityManager.getEntities("tile"))
	//	{
	//		vec2 overlap = Physics::GetOverlap(bullet, tile);
	//		vec2 prevOverlap = Physics::GetPreviousOverlap(bullet, tile);

	//		if (0 < overlap.y && 0 < overlap.x)
	//		{
	//			if (0 <= overlap.x && prevOverlap.x <= 0)
	//			{
	//				if (tile->getComponent<CAnimation>().animation.getName() == "Brick")
	//				{
	//					spawnBrickDebris(tile);
	//				}
	//				bullet->destroy();
	//			}
	//		}
	//	}
	//}

	//for (const auto& coin : m_entityManager.getEntities("coinspin"))
	//{
	//	vec2 overlap = Physics::GetOverlap(coin, m_player);
	//	vec2 prevOverlap = Physics::GetPreviousOverlap(coin, m_player);
	//	if (0 < overlap.y or 0 < overlap.x)
	//	{
	//		if (0 <= overlap.x && prevOverlap.x <= 0)
	//		{
	//			coin->destroy();
	//		}
	//	}

	//}

	//m_player->getComponent<CGravity>().gravity = m_playerConfig.GRAVITY;
	//for (const auto& tile : m_entityManager.getEntities("tile")) {
	//	if (tile->hasComponent<CBoundingBox>())
	//	{
	//		vec2 overlap = Physics::GetOverlap(m_player, tile);
	//		vec2 prevOverlap = Physics::GetPreviousOverlap(m_player, tile);
	//		// check if player is in air
	//		// check tiles being below player
	//		float dy = tile->getComponent<CTransform>().pos.y - m_player->getComponent<CTransform>().pos.y;
	//		if (0 < overlap.x && 0 < overlap.y && dy > 0) {
	//			if (0 <= overlap.y && prevOverlap.y <= 0) {
	//				// stand on tile
	//				m_player->getComponent<CInput>().canJump = true;
	//				m_player->getComponent<CGravity>().gravity = 0;
	//				m_player->getComponent<CTransform>().velocity.y = 0;
	//				// collision resolution
	//				m_player->getComponent<CTransform>().pos.y -= overlap.y;
	//			}
	//		}

	//		if (0 < overlap.x && 0 < overlap.y && dy < 0)
	//		{
	//			if (0 <= overlap.y && prevOverlap.y <= 0)
	//			{
	//				m_player->getComponent<CTransform>().pos.y += overlap.y;
	//				m_player->getComponent<CTransform>().velocity.y = 0;
	//				float delta_x = std::abs(tile->getComponent<CTransform>().pos.x - m_player->getComponent<CTransform>().pos.x);
	//				bool flag = (m_player->getComponent<CTransform>().pos.x - 4.0f) >= (tile->getComponent<CTransform>().pos.x - tile->getComponent<CBoundingBox>().halfSize.x) ||
	//				(m_player->getComponent<CTransform>().pos.x - 4.0f) <= (tile->getComponent<CTransform>().pos.x + tile->getComponent<CBoundingBox>().halfSize.x);
	//				if (tile->getComponent<CAnimation>().animation.getName() == "Question" &&
	//					flag)
	//				{
	//					tile->getComponent<CAnimation>().animation = m_game->assets().getAnimation("QuestionHit");
	//					spawnCoinSpin(tile);
	//				}
	//				else if (tile->getComponent<CAnimation>().animation.getName() == "Brick" &&
	//					flag)
	//				{
	//					spawnBrickDebris(tile);
	//				}
	//			}
	//		}

	//		float dx = tile->getComponent<CTransform>().pos.x - m_player->getComponent<CTransform>().pos.x;
	//		if (0 < overlap.y && -m_gridSize.x < overlap.x)
	//		{

	//			if (0 <= overlap.x && prevOverlap.x <= 0)
	//			{
	//				if (dx > 0)
	//				{
	//					// tile is right of player
	//					m_player->getComponent<CTransform>().pos.x -= overlap.x;
	//				}
	//				else
	//				{
	//					// tile is left of player
	//					m_player->getComponent<CTransform>().pos.x += overlap.x;
	//				}
	//				//m_player->getComponent<CGravity>().gravity = m_playerConfig.GRAVITY;
	//				//m_player->getComponent<CTransform>().pos.y += m_player->getComponent<CGravity>().gravity;
	//			}
	//		}
	//	}
	//}




	//// Check to see if the player has fallen down a hole (y > height())
	//if (m_player->getComponent<CTransform>().pos.y > height())
	//{
	//	m_player->getComponent<CTransform>().pos = gridToMidPixel(m_playerConfig.X, m_playerConfig.Y, m_player);
	//	init(m_levelPath);
	//}
}

void Scene_Play::sDoAction(const Action& action) {
	//std::cout << action.type() << " " << action.name() << std::endl;
	if (action.type() == "START")
	{
		//std::cout << "this is start" << std::endl;
		if (action.name() == "TOGGLE_TEXTURE") { m_drawTextures = !m_drawTextures; }
		else if (action.name() == "TOGGLE_COLLISION") { m_drawCollision = !m_drawCollision; }
		else if (action.name() == "TOGGLE_GRID") { m_drawGrid = !m_drawGrid; }
		else if (action.name() == "PAUSE") { setPaused(!m_paused)	; }
		else if (action.name() == "BACK")
		{
			//m_game->changeScene("MENU", m_game->getScene("MENU"));
			//auto menu_scene = std::make_shared<Scene_Menu>(m_game);
			//std::shared_ptr<Scene> scene = std::dynamic_pointer_cast<Scene>(menu_scene);
			//auto menu = m_game->getScene("MENU");
			//m_game->changeScene("MENU", menu);

			onEnd();
		}
		/*else if (action.name() == "QUIT") { onEnd(); }
		else if (action.name() == "JUMP")
		{
			if (m_player->getComponent<CInput>().canJump)
				m_player->getComponent<CInput>().up = true;
		}
		else if (action.name() == "SHOOT")
		{
			if (m_player->getComponent<CInput>().canShoot)
				m_player->getComponent<CInput>().shoot = true;
		}
		else if (action.name() == "LEFT")
		{
			m_player->getComponent<CInput>().left = true;
		}
		else if (action.name() == "DOWN")
		{
			m_player->getComponent<CInput>().down = true;
		}
		else if (action.name() == "RIGHT")
		{
			m_player->getComponent<CInput>().right = true;
		}*/


	}

	if (action.type() == "END")
	{
		////std::cout << "this is end" << std::endl;
		//if (action.name() == "SHOOT")
		//{
		//	m_player->getComponent<CInput>().shoot = false;
		//}
		//else if (action.name() == "JUMP")
		//{
		//	m_player->getComponent<CInput>().up = false;
		//}
		//else if (action.name() == "LEFT")
		//{
		//	m_player->getComponent<CInput>().left = false;
		//}
		//else if (action.name() == "DOWN")
		//{
		//	m_player->getComponent<CInput>().down = false;
		//}
		//else if (action.name() == "RIGHT")
		//{
		//	m_player->getComponent<CInput>().right = false;
		//}
	}

}

void Scene_Play::changePlayerStateTo(const std::string& state)
{
	/*auto& s = m_player->getComponent<CState>();
	if (s.prevState != state)
	{
		s.prevState = s.state;
		s.state = state;
		s.changeAnimation = true;
	}
	else
	{
		s.changeAnimation = false;
	}*/


}

void Scene_Play::sAnimation() {
	// TODO: Complete the Animation class code first
	//if (m_player->getComponent<CTransform>().velocity.y != 0)
	//{
	//	m_player->getComponent<CInput>().canJump = false;
	//	if (m_player->getComponent<CInput>().shoot)
	//	{
	//		changePlayerStateTo("airshoot");
	//	}
	//	else
	//	{
	//		changePlayerStateTo("air");
	//	}
	//}
	//else
	//{
	//	if (m_player->getComponent<CTransform>().velocity.x != 0)
	//	{
	//		if (m_player->getComponent<CInput>().shoot)
	//		{
	//			changePlayerStateTo("runshoot");
	//		}
	//		else
	//		{
	//			changePlayerStateTo("run");
	//		}
	//	}
	//	else
	//	{
	//		if (m_player->getComponent<CInput>().shoot)
	//		{
	//			changePlayerStateTo("standshoot");
	//		}
	//		else
	//		{
	//			changePlayerStateTo("stand");
	//		}
	//	}
	//}

	//const auto& s = m_player->getComponent<CState>();
	//if (s.changeAnimation)
	//{
	//	std::string animationName;
	//	
	//	if (s.state == "stand")
	//	{
	//		animationName = "Stand";
	//	}
	//	else if (s.state == "air")
	//	{
	//		animationName = "Air";
	//	}
	//	else if (s.state == "run")
	//	{
	//		animationName = "Run";
	//	}
	//	else if (s.state == "standshoot")
	//	{
	//		animationName = "StandShoot";
	//	}
	//	else if (s.state == "runshoot")
	//	{
	//		animationName = "RunShoot";
	//	}
	//	else if (s.state == "airshoot")
	//	{
	//		animationName = "AirShoot";
	//	}

	//	//std::cout << animationName << std::endl;

	//	m_player->addComponent<CAnimation>(m_game->assets().getAnimation(animationName), true);
	//}

	//for (auto& entity : m_entityManager.getEntities())
	//{
	//	if (entity->getComponent<CAnimation>().animation.hasEnded() && !entity->getComponent<CAnimation>().repeat)
	//	{
	//		entity->destroy();
	//	}
	//	if (entity->hasComponent<CAnimation>())
	//	{
	//		entity->getComponent<CAnimation>().animation.update();
	//	}
	//}
}

void Scene_Play::onEnd() {
	// TODO: when the scene ends, change back to the MENU scene
	// use m_game->changeScene(correct params);
	 m_game->changeScene( "PLAY", m_game->getScene("PLAY"));
}

void Scene_Play::sRender() {
	// color the background darker, so you know that the game is paused
	if (!m_paused) {
		m_game->window().clear(sf::Color(192, 138, 126));
	}
	else {
		m_game->window().clear(sf::Color(50, 50, 150));
	}

	// set the viewport of the window to be centered on the player if it's far enough right
	//auto& pPos = m_player->getComponent<CTransform>().pos;
	float windowCenterX = m_game->window().getSize().x / 2.0f;
	float windowCenterY = m_mapSize.y - height() / 2;
	sf::View view = m_game->window().getView();
	////std::cout << "begin " << view.getSize().x << " " << view.getSize().y << std::endl;
	view.setCenter(windowCenterX, windowCenterY);
	//
	//std::cout << "Center: " << m_game->window().getSize().x << " " << m_game->window().getSize().y << std::endl;

	m_game->window().setView(view);
	//std::cout << "View: " << m_game->window().getView().getCenter().x << " " << m_game->window().getView().getCenter().y << std::endl;

	//std::cout << "player: " << m_player->getComponent<CTransform>().pos.x << " " << m_player->getComponent<CTransform>().pos.y << std::endl;

	// draw all Entity textures / animations
	if (m_drawTextures) {
		for (const auto& e : m_entityManager.getEntities()) {
			const auto& transform = e->getComponent<CTransform>();
			//if (e->getComponent<CAnimation>().animation.getName() == "Brick")
			//{
			//	std::cout << e->tag() << " ";
			//	std::cout << e->hasComponent<CBoundingBox>() << " ";
			//	std::cout << e->getComponent<CBoundingBox>().size.x << " " << e->getComponent<CBoundingBox>().size.y << std::endl;
			//}
			if (e->hasComponent<CAnimation>()) {
				auto& animation = e->getComponent<CAnimation>().animation;
				animation.getSprite().setPosition(
					transform.pos.x, transform.pos.y
				);
				animation.getSprite().setScale(
					transform.scale.x, transform.scale.y
				);
				m_game->window().draw(animation.getSprite());
			}
		}
	}

	// draw all Entity collision bounding boxes with a rectangle shape
	if (m_drawCollision) {
		for (const auto& e : m_entityManager.getEntities()) {
			if (e->hasComponent<CBoundingBox>()) {
				auto& box = e->getComponent<CBoundingBox>();
				auto& transform = e->getComponent<CTransform>();
				sf::RectangleShape rect;
				rect.setSize(sf::Vector2f(box.size.x - 1, box.size.y - 1));
				rect.setOrigin(sf::Vector2f(box.halfSize.x, box.halfSize.y));
				rect.setPosition(transform.pos.x, transform.pos.y);
				rect.setFillColor(sf::Color(0, 0, 0, 0));
				rect.setOutlineColor(sf::Color::White);
				rect.setOutlineThickness(1);
				m_game->window().draw(rect);
			}
		}
	}

	// draw the grid so that can easily debug
	if (m_drawGrid) {
		//float leftX = m_game->window().getView().getCenter().x - width() / 2.0;
		//float rightX = leftX + width() + m_gridSize.x;
		//float nextGridX = leftX - ((int)leftX % (int)m_gridSize.x);

		//std::cout << m_game->window().getView().getCenter().x << " " << width() << " " << leftX << " " << rightX << std::endl;
		//std::cout << width() << " " << height() << std::endl;

		float left = m_game->window().getView().getCenter().x - width() / 2.0f;
		float right = left + width() + m_gridSize.x;

		float top = m_game->window().getView().getCenter().y - height() / 2;
		float bottom = top + height() + m_gridSize.y;

		for (float x = left; x < right; x += m_gridSize.x) {
			drawLine(vec2(x, top), vec2(x, bottom));
		}

		for (float y = top; y < bottom; y += m_gridSize.y) {
			drawLine(vec2(0, y), vec2(width(), y));

			//for (float x = 0; x < width(); x += m_gridSize.x) {
			//	std::string xCell = std::to_string((int)x / (int)m_gridSize.x);
			//	std::string yCell = std::to_string((int)y / (int)m_gridSize.y);
			//	m_gridText.setCharacterSize(4);
			//	m_gridText.setString("(" + xCell + "," + yCell + ")");
			//	m_gridText.setPosition(x + 3, height() - y - m_gridSize.y + 2);
			//	m_game->window().draw(m_gridText);
			//}
		}
	}

	drawTitle(m_levelPath);
}

void Scene_Play::spawnCoinSpin(std::shared_ptr<Entity> tile)
{
	/*auto coin = m_entityManager.addEntity("coinspin");
	coin->addComponent<CAnimation>(
		m_game->assets().getAnimation("CoinSpin"),
		true
	);
	coin->addComponent<CTransform>(
		vec2(
			tile->getComponent<CTransform>().pos.x,
			tile->getComponent<CTransform>().pos.y - m_gridSize.y
		),
		vec2(0, 0),
		tile->getComponent<CTransform>().scale,
		0
	);
	coin->addComponent<CBoundingBox>(coin->getComponent<CAnimation>().animation.getSize());
	coin->addComponent<CLifespan>(600, m_currentFrame);*/
}

void Scene_Play::spawnBrickDebris(std::shared_ptr<Entity> tile)
{
	//tile->getComponent<CAnimation>().animation = m_game->assets().getAnimation("Explosion");
	//tile->getComponent<CAnimation>().repeat = false;

	//tile->getComponent<CAnimation>().animation = m_game->assets().getAnimation("BrickDebris");
	//tile->addComponent<CLifespan>(, m_currentFrame);
}


void Scene_Play::drawTitle(std::string level)
{
	std::string level_title = "Lunatics";
	int titleSize = 30;
	sf::Text m_levelText;
	m_levelText.setString(level_title);
	m_levelText.setFont(m_game->assets().getFont("Mario"));
	m_levelText.setCharacterSize(titleSize);
	m_levelText.setFillColor(sf::Color::Black);
	m_levelText.setPosition(
		float(m_game->window().getView().getSize().x) / 2.0f - float(titleSize * (level_title.length() + 1)) / 2.0f,
		float(titleSize * 3)
	);

	m_game->window().draw(m_levelText);
}