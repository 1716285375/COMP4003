#pragma once
#include "Entity.h"
#include "EntityManager.h"

#include <SFML/Graphics.hpp>


struct WindowConfig
{
	int W;
	int H;
	int FL;
	bool FS;
};

struct FontConfig
{
	std::string FF;
	int FS;
	int OR; 
	int OG; 
	int OB;
};

struct PlayerConfig
{
	int SR, CR, FR, FG, FB, OR, OG, OB, OT, V;
	float S;
};

struct EnemyConfig
{
	int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SP;
	float SMIN, SMAX;
};

struct BulletConfig
{
	int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L;
	float S;
};


class Game
{
public:
	Game(const std::string& config);

public:

	void run();

private:
	void init(const std::string& path);
	void setPaused(bool paused);


	// Systems
	void sMovement();
	void sUserInput();
	void sRender();
	void sEnemySpawner();
	void sCollision();

	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemies(const std::shared_ptr<Entity>& entity);
	void spawnBullet(std::shared_ptr<Entity> entity, const CVec2f& mousePos);
	void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

private:
	sf::RenderWindow m_window;
	EntityManager m_entities;
	sf::Font m_font;
	sf::Text m_text;
	WindowConfig m_windowConfig;
	FontConfig m_fontConfig;
	PlayerConfig m_playerConfig;
	EnemyConfig m_enemyConfig;
	BulletConfig m_bulletConfig;
	int m_score = 0;
	int m_currentFrame = 0;
	int m_lastEnemySpawnTime = 0;
	bool m_paused = false;
	bool m_running = true;
	bool m_over = false;

	std::map<std::string, bool> m_keyState;
	std::shared_ptr<Entity> m_player;
};

