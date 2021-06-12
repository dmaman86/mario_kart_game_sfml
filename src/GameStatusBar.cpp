#include "GameStatusBar.h"
#include "Fonts.h"

GameStatusBar::GameStatusBar(sf::RenderWindow& windows) :m_windows(windows){

    m_raceLoc.setFont(Fonts::instance().getFontMario());
    m_lap.setFont(Fonts::instance().getFontMario());
    m_timeGame.setFont(Fonts::instance().getFontMario());
    m_coins.setFont(Fonts::instance().getFontMario());
    m_lap.setCharacterSize(50);
    m_raceLoc.setCharacterSize(50);
    m_timeGame.setCharacterSize(50);
    m_coins.setCharacterSize(50);
}

//====================================================
void GameStatusBar::printGameStatus(const sf::Clock& time, int lap, int raceLoc, int coins) {


    m_lap.setString("Lap:" + std::to_string(lap));

    m_timeGame.setString(timeCalculation(time));

    m_raceLoc.setString("Race:" + std::to_string(raceLoc));
    
    m_coins.setString(std::to_string(coins));

    m_lap.setPosition(800, 800);
    m_raceLoc.setPosition(m_lap.getPosition().x + m_lap.getGlobalBounds().width + 30.f, 809);
    m_timeGame.setPosition(m_raceLoc.getPosition().x + m_raceLoc.getGlobalBounds().width + 30.f, 809);
    m_coins.setPosition(m_timeGame.getPosition().x + m_timeGame.getGlobalBounds().width + 30.f, 809);

    printboard();

}
//====================================================

std::string GameStatusBar::timeCalculation(const sf::Clock& time)
{
    std::string strTime;

    auto seconds = time.getElapsedTime().asSeconds() - 60 * m_minutes;
    auto millieSeconds = (seconds - int(seconds)) * 100;
    if (seconds < 10)
        strTime = "Time: " + std::to_string(m_minutes) + "'" + "0" + std::to_string(int(seconds)) + '"' + std::to_string(int(millieSeconds));
    else
        strTime = "Time: " + std::to_string(m_minutes) + "'" + std::to_string(int(seconds)) + '"' + std::to_string(int(millieSeconds));  //else set it 

    if (seconds > 60)
        m_minutes++;


    return strTime;
}

//====================================================
void GameStatusBar::printboard(){
 
    m_windows.draw(m_lap);
    m_windows.draw(m_timeGame);
    m_windows.draw(m_raceLoc);
    m_windows.draw(m_coins);

}
