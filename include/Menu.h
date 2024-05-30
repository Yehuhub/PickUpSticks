#pragma once

#include <vector>

#include "Button.h"

class Menu{
public:
    Menu();

    void update(const sf::RenderWindow& window);
    bool getActive()const;
    void setActive(bool);
    void draw(sf::RenderWindow& window)const;
    void press(const sf::RenderWindow& window);
    Button* release(const sf::RenderWindow& window);
    void unpressAll();

private:
    std::vector<std::unique_ptr<Button>> m_buttons;
    bool m_active;

};