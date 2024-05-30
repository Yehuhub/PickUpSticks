#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class EndScreen{
public:
    EndScreen() = default;

    void draw(sf::RenderWindow& window, int score)const;

};