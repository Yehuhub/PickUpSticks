#pragma once

#include <SFML/Graphics.hpp>

#include "Button.h"

class ExitButton : public Button{
public:
    ExitButton(const sf::Vector2f& position);
};