#pragma once

#include <unordered_map>

#include <SFML/Graphics.hpp>

const unsigned WINDOWWIDTH = static_cast<unsigned>(sf::VideoMode::getDesktopMode().width * 0.4f);
const unsigned WINDOWHEIGHT = static_cast<unsigned>(sf::VideoMode::getDesktopMode().height * 0.6f);

using Point = sf::Vector2f;

bool onSegment(Point p, Point q, Point r);
int orientation(Point p, Point q, Point r);
bool doIntersect(Point p1, Point q1, Point p2, Point q2);