#pragma once

#include <SFML/Graphics.hpp>

#include "Button.h"

class NewGameButton : public Button{
public:
    NewGameButton(const sf::Vector2f& position);
};