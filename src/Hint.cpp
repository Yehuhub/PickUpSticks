#include "Hint.h"

Hint::Hint(): m_availableToPickup(), m_hintTimer(), m_current(), m_hinting(false){}

void Hint::insertAvailable(Duk* insert){
    for(auto it = m_availableToPickup.begin(); it != m_availableToPickup.end(); it++){
        if((*it).second == insert){
            return;
        }
    }
    m_availableToPickup.insert(std::make_pair(insert->getValue(), insert));
}

void Hint::removeAvailable(Duk* remove){
    std::erase_if(m_availableToPickup, [remove](const auto & pair){return pair.second == remove;});
}

void Hint::startHint(){
    m_hinting = true;
    m_current = m_availableToPickup.begin();
    m_hintTimer.restart();
    (*m_current).second->highLight();
}

void Hint::updateHint(){
    if(!m_hinting){
        return;
    }
    if(m_current == m_availableToPickup.end()){
        m_hinting = false;
    }
    else{
        (*m_current).second->highLight();
    }

    if(m_hintTimer.getElapsedTime() >= sf::Time(sf::seconds(1.f))){
        (*m_current).second->unHighLight();
        m_current++;
        m_hintTimer.restart();
    }

}

int Hint::getAvailableAmnt()const{
    return m_availableToPickup.size();
}

void Hint::stopHint(){
    m_hinting = false;
}

bool Hint::getHinting()const{
    return m_hinting;
}