#include "Scene_Level.h"

#include <iostream>

#include "SFML/Window/Event.hpp"
#include "Scene_Menu.h"
#include "Scene_Play.h"
#include "Assets.h"
#include "GameEngine.h"
#include "Components.h"
#include "Action.h"



Scene_Level::Scene_Level(GameEngine* gameEngine) : Scene(gameEngine) {
	init();
}

void Scene_Level::init() {
	registerAction(sf::Keyboard::W, "UP");
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::Enter, "PLAY");
	registerAction(sf::Keyboard::Escape, "QUIT");

	m_title = "CHOOSE YOUR LEVEL";
	int titleSize = 45;
	int titleDistance = 50;

	m_levelText.setString(m_title);
	m_levelText.setFont(m_game->assets().getFont("Mario"));
	m_levelText.setCharacterSize(titleSize);
	m_levelText.setFillColor(sf::Color(41, 95, 152));
	m_levelText.setPosition(
		float(m_game->window().getSize().x) / 2.0f - float(titleSize * (m_title.length() + 1)) / 2.0f,
		float(titleDistance * 3)
	);

	//std::cout << m_menuText.getGlobalBounds().top << std::endl;
	//std::cout << titleSize * 3 << std::endl;

	std::cout << m_levelText.getPosition().x << " " << m_levelText.getPosition().y << std::endl;


	m_levelStrings.emplace_back("LEVEL 1");
	m_levelStrings.emplace_back("LEVEL 2");
	m_levelStrings.emplace_back("LEVEL 3");

	float textGap = 60.0;
	float textSize = 36.0;

	for (int i = 0; i < m_levelStrings.size(); i++) {
		sf::Text text(m_levelStrings[i], m_game->assets().getFont("Mario"), textSize);
		if (i != m_selectedMenuIndex) {
			text.setFillColor(sf::Color::Black);
		}
		text.setPosition(
			float(m_game->window().getSize().x) / 2.0f - float(26 * (m_levelStrings[i].length() + 1)) / 2.0f,
			m_levelText.getGlobalBounds().top + height() / 10 + textGap * float(i + 1)
		);
		m_levelItems.push_back(text);

		std::cout << "| " << text.getPosition().x << " | " << text.getPosition().y << " |" << std::endl;
	}


	m_levelPaths.emplace_back("./assets/level_1.txt");
	m_levelPaths.emplace_back("./assets/level2.txt");
	m_levelPaths.emplace_back("./assets/level3.txt");


}

void Scene_Level::update() {
	// m_entityManager.update();
	sRender();
}

void Scene_Level::onEnd() {
	m_game->changeScene("MENU", m_game->getScene("MENU"));
}

void Scene_Level::sDoAction(const Action& action) {
	//std::cout << "MENU_ACTION " << action.type() << std::endl;
	if (action.type() == "START") {
		if (action.name() == "UP") {
			if (m_selectedMenuIndex > 0) {

				m_selectedMenuIndex--;
			}
			else {
				m_selectedMenuIndex = m_levelStrings.size() - 1;
			}
		}
		else if (action.name() == "DOWN") {
			m_selectedMenuIndex = (m_selectedMenuIndex + 1) % m_levelStrings.size();
		}
		else if (action.name() == "PLAY") {

			m_game->changeScene(m_levelStrings[m_selectedMenuIndex], std::make_shared<Scene_Play>(m_game, m_levelPaths[m_selectedMenuIndex]));
		}
		else if (action.name() == "QUIT") {
			onEnd();
		}
	}
	else if (action.type() == "END")
	{
		if (action.name() == "UP") {
			std::cout << "UP - end" << std::endl;
		}
		else if (action.name() == "DOWN") {
			std::cout << "DOWN - end" << std::endl;
		}
		else if (action.name() == "PLAY") {
			std::cout << "Play - end" << std::endl;
		}
		else if (action.name() == "QUIT") {
			std::cout << "QUIT - end" << std::endl;
		}
	}
}

void Scene_Level::sRender() {

	// set menu background
	m_game->window().clear(sf::Color(71, 78, 104));

	// draw title
	m_game->window().draw(m_levelText);

	// draw menu items
	for (int i = 0; i < m_levelStrings.size(); i++) {
		if (i != m_selectedMenuIndex) {
			m_levelItems[i].setFillColor(sf::Color::Black);
		}
		else {
			m_levelItems[i].setFillColor(sf::Color::White);
		}

		m_game->window().draw(m_levelItems[i]);
	}

	// draw help
	sf::Text help("W:UP  S:DOWN  ENTER:PLAY  ESC:BACK/QUIT", m_game->assets().getFont("Mario"), 26);
	help.setFillColor(sf::Color::Black);
	help.setPosition(
		float(m_game->window().getSize().x) / 2.0f - float(26 * (help.getString().getSize() + 1)) / 2.0f,
		float(m_game->window().getSize().y) - 35.0f * 2.0f
	);
	m_game->window().draw(help);
}