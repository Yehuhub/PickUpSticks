#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Utilities.h"

const sf::Vector2f dukSize(7,WINDOWWIDTH/4);

class Duk{
public:
    Duk(const sf::Vector2f& position);
    Duk(const sf::Vector2f& position, float angle, int value);
    ~Duk(); //decreases all dukes in below vector

    bool getHighlighted()const; //might not be necessary
    void draw(sf::RenderWindow& window)const;
    void insertBelow(Duk* above);
    bool isIntersectingWith(const Duk& other)const;
    void highLight();
    void unHighLight();
    void highLightAbove();
    void unHighLightAbove();
    const sf::Vector2f& getFirstPosition()const;
    const sf::Vector2f& getSecondPosition()const;
    int getAboveSize() const;
    void insertAbove(Duk*);
    void removeAbove(Duk*);
    bool handleClick(const sf::RenderWindow& window)const;
    int getValue()const;
    float getAngle()const;
    static std::unordered_map<int, sf::Color> getColorsAndValues();

private:
    static std::unordered_map<int, sf::Color> colorsAndValues;

    int m_value;
    float m_angle;
    sf::Vector2f m_firstPosition;
    sf::Vector2f m_secondPosition;
    sf::RectangleShape m_rect;
    bool m_isHighlighted;//might not be necessary
    std::vector<Duk*> m_below;
    std::vector<Duk*> m_above;
};