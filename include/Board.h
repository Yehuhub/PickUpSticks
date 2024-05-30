#pragma once

#include "Duk.h"
#include "Hint.h"
#include "GameInfo.h"
#include "Button.h"

#include <list>
#include <exception>

class Board{
public:
    Board();

    void newGame();
    void loadFromFile();
    void update(sf::RenderWindow& window);
    void hint();
    void draw(sf::RenderWindow& window)const;
    void drawException(sf::RenderWindow& window, std::exception& e)const;
    void insertNewDuk(std::unique_ptr<Duk> newDuk);
    void updateAvailable();
    void mousePress(sf::RenderWindow& window);
    void mouseRelease(sf::RenderWindow& window);
    void save()const;
    bool isNoMoreDuks()const;
    int getScore()const;
    bool isGameTimeOver()const;

private:
    std::list<std::unique_ptr<Duk>> m_duks;
    std::vector<std::unique_ptr<Button>> m_buttons;
    GameInfo m_info;
    Hint m_hint;
};