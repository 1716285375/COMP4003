#pragma once
#include "Scene.h"

#include <map>
#include <memory>
#include <deque>

#include "SFML/Graphics/Text.hpp"
#include "Scene.h"
#include "EntityManager.h"

#ifndef SCENE_LEVEL_H
#define SCENE_LEVEL_H

//typedef std::map<std::string, std::vector<std::string>> levels;

class Scene_Level : public Scene {
protected:
	std::string m_title;
	std::vector<std::string> m_levelStrings;
	std::vector<std::string> m_levelPaths;

	sf::Text m_levelText;
	std::vector<sf::Text> m_levelItems;

	size_t m_selectedMenuIndex = 0;

	void init();

	void update() override;

	void onEnd() override;

	void sDoAction(const Action& action) override;

	// custom implement

public:
	explicit Scene_Level(GameEngine* gameEngine = nullptr);

	void sRender() override;



	// custom implement

};

#endif //SCENE_LEVEL_H
