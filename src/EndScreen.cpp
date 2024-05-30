#include "EndScreen.h"
#include "GameInfo.h"
#include "Utilities.h"

void EndScreen::draw(sf::RenderWindow& window, int score)const{
    sf::Text text;
    std::string print = "Your Score: " + std::to_string(score) +"\n\n Press any key to menu";
    text.setFont(GameInfo::getFont());
    text.setString(print);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);

    sf::FloatRect bounds = text.getGlobalBounds();
    sf::Vector2f textPos(static_cast<float>(WINDOWWIDTH/2 - bounds.width/2), (WINDOWHEIGHT/2 - bounds.height*2));

    text.setPosition(textPos);

    window.draw(text);
}