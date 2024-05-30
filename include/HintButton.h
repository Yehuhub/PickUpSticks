#pragma once

#include <SFML/Graphics.hpp>

#include "Button.h"

class HintButton : public Button{
public:
    HintButton(const sf::Vector2f& position);
};