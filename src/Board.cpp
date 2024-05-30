#include "Board.h"
#include "Utilities.h"
#include "FileTemplateError.h"
#include "OutOfRangeError.h"
#include "OpenFileError.h"
#include "SaveButton.h"
#include "ExitButton.h"
#include "HintButton.h"

#include <sstream>
#include <fstream>
#include <iostream>//for debugging

Board::Board(): m_duks(), m_info(), m_hint(){
    m_buttons.push_back(std::make_unique<ExitButton>(sf::Vector2f(3, WINDOWHEIGHT/10 * 7)));
    m_buttons.push_back(std::make_unique<SaveButton>(sf::Vector2f(WINDOWWIDTH - buttonSize.x - 3 ,WINDOWHEIGHT/10 * 7)));
    m_buttons.push_back(std::make_unique<HintButton>(sf::Vector2f(WINDOWWIDTH - buttonSize.x - 3 ,WINDOWHEIGHT/10 * 7 - buttonSize.y - 3)));
};

//randomizes duk and time for the game
void Board::newGame(){
    sf::Vector2f pos;
    int dukAmnt = rand() % WINDOWWIDTH/15;
    for(int i = 0 ; i < 3 ; i++){ // change to dukamnt
        //make sure duks are positioned nicely
        pos.x = rand() % (WINDOWWIDTH - static_cast<int>(dukSize.y) * 2) + dukSize.y;
        pos.y = rand() % (WINDOWHEIGHT - static_cast<int>(dukSize.y) * 3) + dukSize.y;

        insertNewDuk(std::make_unique<Duk>(pos)); 
    }
    m_info.resetInfo();
    m_info.setGameTime(sf::Time(sf::seconds(3 * 2)));//2 seconds for each duk //change back to dukAmnt
    updateAvailable();
}

//.duk files need to be in the format:
//t(time as seconds)
//s(score)
//x(x position) y(y position) a(angle) v(value) 
void Board::loadFromFile(){
    std::ifstream levelFile("gamesave.duk");
    std::string inputLine;
    int valCounter;
    int tempValue;

    if(!levelFile.is_open()){
        throw OpenFileError();
    }

    getline(levelFile, inputLine);//get time left in seconds
    tempValue = std::stoi(inputLine);
    if(tempValue < 0){
        throw OutOfRangeError();
    }
    m_info.setGameTime(sf::Time(sf::seconds(tempValue))); 

    getline(levelFile, inputLine);//get score
    tempValue = std::stoi(inputLine);
    if(tempValue < 0){
        throw OutOfRangeError();
    }
    m_info.setScore(tempValue);

    getline(levelFile, inputLine);//get amount of duks already lifted
    tempValue = std::stoi(inputLine);
    if(tempValue < 0){
        throw OutOfRangeError();
    }
    m_info.setLifted(tempValue);

    while(getline(levelFile, inputLine)){
        valCounter = 0;
        std::istringstream is(inputLine);
        int value;
        float x, y, angle;

        while(is >> x){
            valCounter++;
        }

        if(valCounter != 4){
            throw FileTemplateError();
        }
        is.clear();
        is.seekg(std::ios::beg);

        if(!(is >> x >> y >> angle >> value)){
            throw FileTemplateError();
        }

        if(angle < 0 || (x < 0 + dukSize.y) || (x > WINDOWWIDTH - dukSize.y) || 
            (y > WINDOWHEIGHT - dukSize.y) || (y < 0 + dukSize.y) || 
            (Duk::getColorsAndValues().find(value) == Duk::getColorsAndValues().end())){
            throw OutOfRangeError();
        }

        insertNewDuk(std::make_unique<Duk>(sf::Vector2f(x, y), angle, value));

    }
    updateAvailable();
    levelFile.close();

}


void Board::insertNewDuk(std::unique_ptr<Duk> newDuk){
    for(auto& oldDuk : m_duks){
        if(newDuk->isIntersectingWith(*oldDuk)){
            oldDuk->insertAbove(newDuk.get());
            //each duk vector of raw pointers to duks below it
            newDuk->insertBelow(oldDuk.get());
        }
    }

    //duks are inserted to the front of the list so that they can be destroyed first
    m_duks.push_front(std::move(newDuk));
}

void Board::updateAvailable(){
    for(auto& duk : m_duks){
        if(duk->getAboveSize() == 0){
            m_hint.insertAvailable(duk.get());
        }
    }
}

void Board::draw(sf::RenderWindow& window)const{
    for(auto it = m_duks.rbegin(); it != m_duks.rend(); it++){
        (*it)->draw(window);
    }
    for(auto& btn : m_buttons){
        btn->drawButton(window);
    }
    m_info.drawInfo(window, m_hint.getAvailableAmnt(), m_duks.size());
}

void Board::update(sf::RenderWindow& window){
    for(auto& btn : m_buttons){
        btn->update(window);
    }
    m_hint.updateHint();

}

void Board::hint(){
    m_hint.startHint();
}

void Board::mousePress(sf::RenderWindow& window){
    if(m_hint.getHinting()){
        m_hint.stopHint();
        return;
    }
    for(auto it = m_duks.begin() ; it != m_duks.end(); it++){
        if((*it)->handleClick(window)){
            if((*it)->getAboveSize() == 0){

                //remove from the list
                auto toDelete = std::move(*it);
                it = m_duks.erase(it);

                //erase the pointer from the available to pickup vector
                m_hint.removeAvailable(toDelete.get());

                //increase score
                m_info.increaseScore(toDelete->getValue());

                //check if there are any new avaialable for pickup
                updateAvailable();
                m_info.increaseLifted(1);
                break;
            }
            else{
                (*it)->highLightAbove();
                break;
            }
        }
    }
    for(auto& btn : m_buttons){
        btn->press(window);
    }

}

void Board::mouseRelease(sf::RenderWindow& window){
    for(auto it = m_duks.begin() ; it != m_duks.end(); it++){
        (*it)->unHighLightAbove();    
    }
    for(auto& btn : m_buttons){
        Button* btnPtr = btn->release(window);
        if(ExitButton* eb = dynamic_cast<ExitButton*>(btnPtr)){
            exit(EXIT_SUCCESS);
        }
        else if(HintButton* hb = dynamic_cast<HintButton*>(btnPtr)){
            hint();
        }
        else if(SaveButton* sb = dynamic_cast<SaveButton*>(btnPtr)){
            try{
                save();
            }
            catch(std::exception & e){
                drawException(window,e);
            }
        }
    }
    for(auto& btn : m_buttons){
        btn->unpress();
    }
}

//.duk files need to be in the format:
//t(time as seconds)
//s(score)
//x(x position) y(y position) a(angle) v(value) 
void Board::save()const{
    
    std::ofstream saveFile("gamesave.duk");

    if(!saveFile.is_open()){
        throw OpenFileError();
    }

    //time left
    saveFile<<(m_info.getLevelTime().asSeconds() - m_info.getElapsedTime().asSeconds())<<std::endl;
    //score
    saveFile<<m_info.getScore()<<std::endl;
    //duks lifted
    saveFile<<m_info.getLifted()<<std::endl;

    for(auto& duk : m_duks){
        //duk data
        saveFile<< duk->getFirstPosition().x <<" "<<duk->getFirstPosition().y<<" "
            <<duk->getAngle()<<" "<<duk->getValue()<<std::endl; 
    }

    saveFile.close();
    
}

void Board::drawException(sf::RenderWindow& window, std::exception& e)const{
    sf::RectangleShape errorBox;
    sf::Text errorMsg(e.what(),GameInfo::getFont(),20);


    errorBox.setSize(sf::Vector2f(WINDOWWIDTH/3, 200));
    errorBox.setPosition(sf::Vector2f(WINDOWWIDTH/2 - (WINDOWWIDTH/3)/2, WINDOWHEIGHT/3 - 200/2));
    errorBox.setFillColor(sf::Color::Red);


    errorMsg.setCharacterSize(30);

    sf::FloatRect textBounds = errorMsg.getLocalBounds();
    float textX = errorBox.getPosition().x + (WINDOWWIDTH/3 - textBounds.width) / 2.0f;
    float textY = errorBox.getPosition().y + (200 - textBounds.height) / 2.0f;
    errorMsg.setPosition(textX, textY);
    errorMsg.setOutlineColor(sf::Color::Black);
    
    window.draw(errorBox);
    window.draw(errorMsg);
    window.display();
    sf::sleep(sf::Time(sf::seconds(2)));
}

bool Board::isNoMoreDuks()const{
    return m_duks.empty();
}
int Board::getScore()const{
    return m_info.getScore();
}

bool Board::isGameTimeOver()const{
    if(m_info.getLevelTime().asSeconds() - m_info.getElapsedTime().asSeconds() <= 0){
        return true;
    }
    return false;
}