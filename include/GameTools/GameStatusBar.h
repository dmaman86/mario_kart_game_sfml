#pragma once
#include <SFML/Graphics.hpp>
#include "MarioKart.h"

//GameStatusBar 
class GameStatusBar {

public:
	//============ Constructor =======================
    GameStatusBar(sf::RenderWindow& data);

	//============ Public Functions ==================
    void printGameStatus(const sf::Time &time, int lap, int coins,
                         int coinsfrom, int racelaps);
private:
    //========= private members ======================
    sf::Text m_raceLoc;
    sf::Text m_lap;
    sf::Text m_timeGame;
    sf::Text m_coins;
    sf::RenderWindow& m_windows;
    int m_minutes;
    
	//========= private function ======================
    std::string timeCalculation(const sf::Time& time);
    void printboard();

};//end GameStatusBar