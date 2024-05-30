#include "Duk.h"
#include "Utilities.h"
#include <cmath>
#include <algorithm>
#include <iostream> //for debugging


std::unordered_map<int, sf::Color> Duk::colorsAndValues = {
    {10, sf::Color::Red}, {20, sf::Color::Green}, {30, sf::Color::Blue},
    {40, sf::Color::Cyan}, {50, sf::Color::Black}, {60, sf::Color(160, 32, 240)}
};

Duk::Duk(const sf::Vector2f& position)
    :m_firstPosition(position), m_rect(dukSize), m_below(), m_above(){

        m_value = (rand() % static_cast<int>(colorsAndValues.size()) + 1) * 10;
        m_angle = (rand() % 360);

        m_rect.setPosition(position);
        m_rect.setRotation(m_angle);

        //will only change outline thickness when highlighted
        m_rect.setOutlineColor(sf::Color::Yellow); 
        m_rect.setFillColor(colorsAndValues[m_value]);


        sf::Vector2f offset(0, dukSize.y);
        m_secondPosition = m_rect.getTransform().transformPoint(offset);
}

Duk::Duk(const sf::Vector2f& position, float angle, int value)
    : m_value(value), m_angle(angle), m_firstPosition(position), m_rect(dukSize), m_below(), m_above() {

    m_rect.setPosition(position);
    m_rect.setRotation(m_angle);

    m_rect.setOutlineColor(sf::Color::Yellow); 
    m_rect.setFillColor(colorsAndValues[m_value]);


    sf::Vector2f offset(0, dukSize.y);
    m_secondPosition = m_rect.getTransform().transformPoint(offset);
}

Duk::~Duk(){
    for(auto& duk : m_below){
        duk->removeAbove(this);
    }
}

bool Duk::getHighlighted()const{
    return m_isHighlighted;
}

void Duk::draw(sf::RenderWindow& window)const{
    window.draw(m_rect);
}

void Duk::highLight(){
    m_isHighlighted = true;
    m_rect.setOutlineThickness(2);
}

void Duk::unHighLight(){
    m_isHighlighted = false;
    m_rect.setOutlineThickness(0);
}
void Duk::insertBelow(Duk* below){
    m_below.push_back(below);
}

const sf::Vector2f& Duk::getFirstPosition()const{
    return m_firstPosition;
}

const sf::Vector2f& Duk::getSecondPosition()const{
    return m_secondPosition;
}

bool Duk::isIntersectingWith(const Duk& other)const{
    return doIntersect(m_firstPosition, m_secondPosition, other.getFirstPosition(), other.getSecondPosition());
}

void Duk::insertAbove(Duk* other){
    m_above.push_back(other);
}

void Duk::removeAbove(Duk* other){
    std::erase_if(m_above, [other](Duk* toFind){return other == toFind;});
}

int Duk::getAboveSize()const{
    return m_above.size();
}

bool Duk::handleClick(const sf::RenderWindow& window)const{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePositionF (static_cast<float>(mousePosition.x),static_cast<float>(mousePosition.y));

    const auto transformedPoint = m_rect.getTransform().getInverse().transformPoint(mousePositionF);

    if(m_rect.getLocalBounds().contains(transformedPoint)){
        return true;
    }
    else
        return false;
}

void Duk::highLightAbove(){
    for(auto& duk : m_above){
        duk->highLight();
    }
}
void Duk::unHighLightAbove(){
    for(auto& duk : m_above){
        duk->unHighLight();
    }
}

int Duk::getValue()const{
    return m_value;
}

std::unordered_map<int, sf::Color> Duk::getColorsAndValues(){
    return colorsAndValues;
}

float Duk::getAngle()const{
    return m_angle;
}