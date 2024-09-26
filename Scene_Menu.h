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

    size_t m_selectedMenuIndex = 0;

    // custom variable

    void init();

    void update() override;

    void onEnd() override;

    void sDoAction(const Action &action) override;

    // custom implement

public:
    explicit Scene_Menu(GameEngine *gameEngine = nullptr);

    void sRender() override;



    // custom implement
};

#endif //SCENE_MENU_H
