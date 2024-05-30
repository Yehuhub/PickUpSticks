#pragma once

#include <SFML/Graphics.hpp>

class GameInfo{
public:
    GameInfo();

    sf::Time getElapsedTime()const;
    sf::Time getLevelTime()const;
    void resetTimer();
    int getScore()const;
    void increaseScore(int);
    void setScore(int);
    void setGameTime(sf::Time);
    static sf::Font& getFont();
    void setLifted(int);
    void increaseLifted(int amnt);
    int getLifted()const;
    void resetInfo();
    void drawInfo(sf::RenderWindow& window, int available, int all)const;


private:
    static sf::Font m_font;

    sf::Clock m_gameTimer;
    sf::Time m_levelTime;
    int m_score;
    int m_lifted;
};