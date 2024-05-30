#include "Menu.h"
#include "Utilities.h"

#include "ExitButton.h"
#include "LoadButton.h"
#include "NewGameButton.h"

Menu::Menu(): m_active(true){
    m_buttons.push_back(std::make_unique<NewGameButton>(sf::Vector2f(static_cast<float>(WINDOWWIDTH/2 - buttonSize.x/2), static_cast<float>(WINDOWHEIGHT/8 * 1))));
    m_buttons.push_back(std::make_unique<LoadButton>(sf::Vector2f(static_cast<float>(WINDOWWIDTH/2 - buttonSize.x/2), static_cast<float>(WINDOWHEIGHT/8 * 3))));
    m_buttons.push_back(std::make_unique<ExitButton>(sf::Vector2f(static_cast<float>(WINDOWWIDTH/2 - buttonSize.x/2), static_cast<float>(WINDOWHEIGHT/8 * 5))));
}

bool Menu::getActive()const{
    return m_active;
}

void Menu::setActive(bool setActivity){
    m_active = setActivity;
}

void Menu::update(const sf::RenderWindow& window){
    for(auto& button : m_buttons){
        button->update(window);
    }
}

void Menu::draw(sf::RenderWindow& window)const{
    for(auto& button : m_buttons){
        button->drawButton(window);
    }
}

void Menu::press(const sf::RenderWindow& window){
    for(auto& button : m_buttons){
        button->press(window);
    }
}

Button* Menu::release(const sf::RenderWindow& window){
    Button* btnPtr = nullptr;
    for(auto& button : m_buttons){
        btnPtr = button->release(window);
        if(btnPtr != nullptr){
            return btnPtr;
        }
    }
    return nullptr;
}

void Menu::unpressAll(){
    for(auto& btn : m_buttons){
        btn->unpress();
    }
}
