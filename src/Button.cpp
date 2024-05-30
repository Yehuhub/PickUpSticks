#include "Button.h"

#include <string>

#include "Utilities.h"

sf::Font Button::m_font;

Button::Button(const sf::Vector2f& position, std::string text): m_hovered(false), m_pressed(false){
    
    m_font.loadFromFile("FONT.ttf");

    //set rect properties
    m_rect.setOutlineColor(sf::Color::White);
    m_rect.setOutlineThickness(2);
    m_rect.setSize(buttonSize);
    m_rect.setFillColor(sf::Color::Black);
    m_rect.setPosition(position);

    //set text properties
    m_buttonText.setString(text);
    m_buttonText.setFillColor(sf::Color::White);
    m_buttonText.setCharacterSize(24);
    m_buttonText.setFont(m_font);

    //center text in button
    sf::FloatRect textBounds = m_buttonText.getLocalBounds();
    float textX = position.x + (buttonSize.x - textBounds.width) / 2.0f;
    float textY = position.y + (buttonSize.y - textBounds.height) / 2.0f;
    m_buttonText.setPosition(textX, textY);

}

void Button::drawButton(sf::RenderWindow& window)const{
    window.draw(m_rect);
    window.draw(m_buttonText);
}

void Button::unpress(){
    if(m_pressed){
        m_pressed = false;
    }
}

bool Button::getPressed()const{
    return m_pressed;
}

void Button::update(const sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePositionF (static_cast<float>(mousePosition.x),static_cast<float>(mousePosition.y));

    if(!m_hovered && m_rect.getGlobalBounds().contains(mousePositionF)){
        m_hovered = true;
        m_rect.setFillColor(sf::Color(51,51,51));//slightly gray
    }
    else if(m_hovered && !(m_rect.getGlobalBounds().contains(mousePositionF))){
        m_hovered = false;
        m_rect.setFillColor(sf::Color::Black);
    }
}

void Button::press(const sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePositionF (static_cast<float>(mousePosition.x),static_cast<float>(mousePosition.y));

    if(m_rect.getGlobalBounds().contains(mousePositionF)){
       m_buttonText.setFillColor(sf::Color::Red);
    }
}

Button* Button::release(const sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePositionF (static_cast<float>(mousePosition.x),static_cast<float>(mousePosition.y));

    if(m_buttonText.getFillColor() == sf::Color::Red){
        m_buttonText.setFillColor(sf::Color::White);
    }

    if(!m_pressed && m_rect.getGlobalBounds().contains(mousePositionF)){
        m_pressed = true;
        return this;
    }
    return nullptr;
}