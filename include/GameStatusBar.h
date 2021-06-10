#pragma once
#include <SFML/Graphics.hpp>

class GameStatusBar {


public:
    GameStatusBar();
    void printGameStatus(sf::RenderWindow&, const sf::Time&, const sf::Clock&, bool,
        int score, int lap);

private:
    //=========private members======================
    sf::Text m_scoreText;
    sf::Text m_levelText;
    sf::Text m_lifeText;
    sf::Text m_timeTheLevel;
    int m_life, m_score;
    sf::Time m_time, m_lifechange, m_scorechange, m_timechange;

    //=========private function======================

    void printboard(sf::RenderWindow& window);
    void printChangeColor(int life, const sf::Clock& clock,
        const sf::Time& time, int score);
};