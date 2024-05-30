#include "GameInfo.h"

#include <string>   

#include "Utilities.h"

sf::Font GameInfo::m_font;

GameInfo::GameInfo(): m_gameTimer(), m_levelTime(),m_score(0), m_lifted(0){
    m_font.loadFromFile("FONT.ttf");
}

sf::Time GameInfo::getElapsedTime()const{
    return m_gameTimer.getElapsedTime();
}

void GameInfo::resetTimer(){
    m_gameTimer.restart();
}

int GameInfo::getScore()const{
    return m_score;
}

void GameInfo::increaseScore(int add){
    m_score += add;
}

void GameInfo::setGameTime(sf::Time levelTime){
    m_gameTimer.restart();
    m_levelTime = levelTime;
}

void GameInfo::setScore(int score){
    m_score = score;
}

sf::Time GameInfo::getLevelTime()const{
    return m_levelTime;
}

void GameInfo::drawInfo(sf::RenderWindow& window, int available, int all)const{
    sf::Text text;

    std::string timeString = "Time left: ";
    std::string scoreString = "Score: " + std::to_string(m_score);
    std::string availableString = "Availabale: " + std::to_string(available);
    std::string total = "Total Duks : "+ std::to_string(all);
    std::string liftedDukes = "Dukes lifted: "+ std::to_string(m_lifted);


    text.setFont(m_font);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);

    int asSeconds = static_cast<int>(m_levelTime.asSeconds() - m_gameTimer.getElapsedTime().asSeconds());

    timeString += std::to_string(asSeconds/60) + ":" + std::to_string(asSeconds % 60);

    text.setString(timeString);
    text.setPosition({static_cast<float>(WINDOWWIDTH/8 * 6), static_cast<float>(WINDOWHEIGHT/32 * 1)});
    window.draw(text);


    text.setString(scoreString);
    text.setPosition({static_cast<float>(WINDOWWIDTH/8 * 6), static_cast<float>(WINDOWHEIGHT/32 * 2)});
    window.draw(text);

    text.setString(availableString);
    text.setPosition({static_cast<float>(WINDOWWIDTH/8 * 6), static_cast<float>(WINDOWHEIGHT/32 * 3)});
    window.draw(text);

    text.setString(total);
    text.setPosition({static_cast<float>(WINDOWWIDTH/8 * 6), static_cast<float>(WINDOWHEIGHT/32 * 4)});
    window.draw(text);
    
    text.setString(liftedDukes);
    text.setPosition({static_cast<float>(WINDOWWIDTH/8 * 6), static_cast<float>(WINDOWHEIGHT/32 * 5)});
    window.draw(text);
}

sf::Font& GameInfo::getFont(){
    return m_font;
}

void GameInfo::setLifted(int lifted){
    m_lifted = lifted;
}
void GameInfo::increaseLifted(int amnt){
    m_lifted += amnt;
}
int GameInfo::getLifted()const{
    return m_lifted;
}
void GameInfo::resetInfo(){
    m_score = 0;
    m_lifted = 0;
}