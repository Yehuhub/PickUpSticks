#include "Controller.h"
#include "Utilities.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ExitButton.h"
#include "LoadButton.h"
#include "NewGameButton.h"
#include "OpenFileError.h"


Controller::Controller()
    : m_board(), m_window(), m_menu(), m_game(false), m_endScreen(false){

    m_window.create(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "DUUUUKS");
    srand(time(NULL));

}

void Controller::game(){
    
    
    while(m_window.isOpen()){
        m_window.clear(sf::Color(128,128,128));//gray
        draw();
        
        m_window.display();

        for (auto event = sf::Event{}; m_window.pollEvent(event); ) {
            switch(event.type){
                case sf::Event::Closed:
                    m_window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    mousePress();
                    break;
                case sf::Event::MouseButtonReleased:
                    mouseRelease();
                    break;
                case sf::Event::KeyPressed:
                    if(m_endScreen){
                        m_endScreen = false;
                        m_menu.setActive(true);
                    }
                    break;
                default:
                    break;
            }
        }
        
        update();
    }
}

void Controller::draw(){
    if(m_game){
        m_board.draw(m_window);
    }
    else if(m_menu.getActive()){
        m_menu.draw(m_window);
    }
    else if(m_endScreen){
        m_end.draw(m_window, m_board.getScore());
    }
}

void Controller::update(){

    if(m_game){
        m_board.update(m_window);
    }
    else if(m_menu.getActive()){
        m_menu.update(m_window);
    }

    if(m_board.isNoMoreDuks() || m_board.isGameTimeOver()){
        m_game = false;
        m_endScreen = true;
    }
}

void Controller::mousePress(){
    if(m_game){
        m_board.mousePress(m_window);
    }
    else if(m_menu.getActive()){
        m_menu.press(m_window);
    }
    else if(m_endScreen){
        m_endScreen = false;
        m_menu.setActive(true);
    }
    
}

void Controller::mouseRelease(){
    if(m_game){
        m_board.mouseRelease(m_window);
    }
    else if(m_menu.getActive()){
        Button* btnPtr = m_menu.release(m_window);
        if(ExitButton* eb = dynamic_cast<ExitButton*>(btnPtr)){
            exit(EXIT_SUCCESS);
        }
        else if(NewGameButton* ngb = dynamic_cast<NewGameButton*>(btnPtr)){
            m_menu.setActive(false);
            m_board.newGame();
            m_game = true;
        }
        else if(LoadButton* lb = dynamic_cast<LoadButton*>(btnPtr)){
            try{
            m_board.loadFromFile();
            m_menu.setActive(false);
            m_game = true;
            }
            catch (std::exception & e){
                m_board.drawException(m_window, e);
            }
        }
        m_menu.unpressAll();
    }
}
