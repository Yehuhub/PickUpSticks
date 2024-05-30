#pragma once

#include <map>

#include "Duk.h"


class Hint{
public:
    Hint();

    void insertAvailable(Duk*);
    void removeAvailable(Duk*);
    void updateHint();
    void startHint();
    void stopHint();
    bool getHinting()const;
    int getAvailableAmnt()const;

private:
    //int for value(map sorts all available duks by their value)
    std::multimap<int, Duk*, std::greater<int>> m_availableToPickup;
    sf::Clock m_hintTimer;
    std::multimap<int,Duk*>::iterator m_current;
    bool m_hinting;

};