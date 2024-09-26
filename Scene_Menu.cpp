#include <iostream>

#include "SFML/Window/Event.hpp"
#include "Scene_Menu.h"
#include "Scene_Play.h"
#include "Scene_Level.h"
#include "Physics.h"
#include "Assets.h"
#include "GameEngine.h"
#include "Components.h"
#include "Action.h"


Scene_Menu::Scene_Menu(GameEngine *gameEngine) : Scene(gameEngine) {
    init();
}

void Scene_Menu::init() {
    registerAction(sf::Keyboard::W, "UP");
    registerAction(sf::Keyboard::S, "DOWN");
    registerAction(sf::Keyboard::Enter, "PLAY");
    registerAction(sf::Keyboard::Escape, "QUIT");

    m_title = "MEGMAN VS MARIO";
    int titleSize = 45;
    int titleDistance = 50;

    m_menuText.setString(m_title);
    m_menuText.setFont(m_game->assets().getFont("Mario"));
    m_menuText.setCharacterSize(titleSize);
    m_menuText.setFillColor(sf::Color(41, 95, 152));
    m_menuText.setPosition(
            float(m_game->window().getSize().x) / 2.0f - float(titleSize * (m_title.length() + 1)) / 2.0f,
            float(titleDistance * 3)
    );
    
    //std::cout << m_menuText.getGlobalBounds().top << std::endl;
    //std::cout << titleSize * 3 << std::endl;

    std::cout << m_menuText.getPosition().x << " " << m_menuText.getPosition().y << std::endl;

    m_menuStrings.emplace_back("PLAY");
    m_menuStrings.emplace_back("LEVEL EDIT");
    m_menuStrings.emplace_back("SETTING");
    m_menuStrings.emplace_back("ABOUT");

    float textGap = 45.0;

    for (int i = 0; i < m_menuStrings.size(); i++) {
        sf::Text text(m_menuStrings[i], m_game->assets().getFont("Mario"), 26);
        if (i != m_selectedMenuIndex) {
            text.setFillColor(sf::Color::Black);
        }
        text.setPosition(
                float(m_game->window().getSize().x) / 2.0f - float(26 * (m_menuStrings[i].length() + 1)) / 2.0f,
                m_menuText.getGlobalBounds().top + height() / 10 + textGap * float(i + 1)
        );
        m_menuItems.push_back(text);

        std::cout << "| " << text.getPosition().x << " | " << text.getPosition().y << " |" << std::endl;
    }
}

void Scene_Menu::update() {
    // m_entityManager.update();
    sRender();
}

void Scene_Menu::onEnd() {
    m_game->quit();
}

void Scene_Menu::sDoAction(const Action &action) {
    //std::cout << "MENU_ACTION " << action.type() << std::endl;
    if (action.type() == "START") {
        if (action.name() == "UP") {
            if (m_selectedMenuIndex > 0) {
                m_selectedMenuIndex--;
            } else {
                m_selectedMenuIndex = m_menuStrings.size() - 1;
            }
        } else if (action.name() == "DOWN") {
            m_selectedMenuIndex = (m_selectedMenuIndex + 1) % m_menuStrings.size();
        } else if (action.name() == "PLAY") {
            if (m_menuStrings[m_selectedMenuIndex] == "PLAY")
                m_game->changeScene("PLAY", std::make_shared<Scene_Level>(m_game));
            if (m_menuStrings[m_selectedMenuIndex] == "LEVEL EDIT");
            if (m_menuStrings[m_selectedMenuIndex] == "SETTING");
            if (m_menuStrings[m_selectedMenuIndex] == "ABOUT");

        } else if (action.name() == "QUIT") {
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

void Scene_Menu::sRender() {

	// set menu background
	m_game->window().clear(sf::Color(71, 78, 104));

	// draw title
	m_game->window().draw(m_menuText);

	// draw menu items
	for (int i = 0; i < m_menuStrings.size(); i++) {
		if (i != m_selectedMenuIndex) {
			m_menuItems[i].setFillColor(sf::Color::Black);
		}
		else {
			m_menuItems[i].setFillColor(sf::Color::White);
		}

		m_game->window().draw(m_menuItems[i]);
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

