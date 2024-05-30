#pragma once

#include <SFML/Graphics.hpp>

const sf::Vector2f buttonSize(200.f, 70.f);

class Button{
public:
    Button(const sf::Vector2f&, std::string text);
    virtual ~Button() = default;
    void update(const sf::RenderWindow& window);
    void drawButton(sf::RenderWindow&)const;
    void unpress();
    bool getPressed()const;
    void press(const sf::RenderWindow& window);
    Button* release(const sf::RenderWindow& window);

private:
    static sf::Font m_font;

    sf::RectangleShape m_rect;
    sf::Text m_buttonText;
    bool m_hovered;
    bool m_pressed;
};