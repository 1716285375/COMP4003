#ifndef SCENE_MENU_H
#define SCENE_MENU_H

#include <map>
#include <memory>
#include <deque>

#include "SFML/Graphics/Text.hpp"
#include "Scene.h"
#include "EntityManager.h"


class Scene_Menu : public Scene {
protected:
    std::string m_title;
    std::vector<std::string> m_menuStrings;

    sf::Text m_menuText;
    std::vector<sf::Text> m_menuItems;

    std::vector<std::string> m_levelPaths;
    size_t m_selectedMenuIndex = 0;

    void init();

    void update() override;

    void onEnd() override;

    void sDoAction(const Action &action) override;

public:
    explicit Scene_Menu(GameEngine *gameEngine = nullptr);

    void sRender() override;

    void setLevel(size_t index)
    {
        m_selectedMenuIndex = index;

    }

    size_t getLevelIndex(std::string levelPath)
    {
        auto index = 0;
		for ( auto i = 0; i < m_levelPaths.size(); ++i)
		{
            if (m_levelPaths[i] == levelPath)
            {
                index = i;
                break;
            }

		}

        return index;
    }
};

#endif //SCENE_MENU_H
