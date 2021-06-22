#pragma once
#include <SFML/Graphics.hpp>
#include "MarioKart.h"
class GameStatusBar {


public:
    GameStatusBar(sf::RenderWindow& data);
    void printGameStatus(const sf::Time &time, int lap, int coins,
                         int coinsfrom, int racelaps);

private:
    //=========private members======================
    sf::Text m_raceLoc;
    sf::Text m_lap;
    sf::Text m_timeGame;
    sf::Text m_coins;
    sf::RenderWindow& m_windows;

    int m_minutes = 0;
    //=========private function======================
    std::string timeCalculation(const sf::Time& time);
    void printboard();

};