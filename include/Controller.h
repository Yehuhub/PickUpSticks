#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>

#include "Menu.h"
#include "Board.h"
#include "EndScreen.h"

class Controller{
public:
    Controller();

    void game();
    void draw();
    void update(); 
    void mousePress();
    void mouseRelease();


private:
    Board m_board;
    sf::RenderWindow m_window;
    Menu m_menu;
    EndScreen m_end;
    bool m_game;
    bool m_endScreen;
};