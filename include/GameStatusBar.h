#pragma once
#include <SFML/Graphics.hpp>
#include "MarioKart.h"
class GameStatusBar {


public:
    GameStatusBar(sf::RenderWindow& data);
    void printGameStatus(const sf::Clock&, int , int, int);

private:
    //=========private members======================
    sf::Text m_raceLoc;
    sf::Text m_lap;
    sf::Text m_timeGame;
    sf::Text m_coins;
    sf::RenderWindow& m_windows;

    int m_minutes = 0;
    //=========private function======================
    std::string timeCalculation(const sf::Clock& time);
    void printboard();

};