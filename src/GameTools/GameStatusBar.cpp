#include "GameStatusBar.h"
#include "Fonts.h"
#include "MacrosGameTools.h"

//================== Constructor ======================
GameStatusBar::GameStatusBar
	(sf::RenderWindow& windows) :m_windows(windows), m_minutes(0)
{
    m_raceLoc.setFont(Fonts::instance().getFontMario());
    m_lap.setFont(Fonts::instance().getFontMario());
    m_timeGame.setFont(Fonts::instance().getFontMario());
    m_lap.setCharacterSize(CHATACTER_SIZE);
    m_raceLoc.setCharacterSize(CHATACTER_SIZE);
    m_timeGame.setCharacterSize(CHATACTER_SIZE);
}

//====================================================
void GameStatusBar::printGameStatus(const sf::Time &time, int lap, int coins,
                                    int coinsfrom, int racelaps) 
{
    if(racelaps > 0)
        m_lap.setString("Lap:" + std::to_string(lap) +
						"/" +std::to_string(racelaps));
    else
        m_lap.setString("Lap:" + std::to_string(lap) +
						"/" +std::to_string(racelaps));

    m_timeGame.setString(timeCalculation(time));

    m_raceLoc.setString("Coins:" + std::to_string(coins) +
						"/" +std::to_string(coinsfrom));

    m_lap.setPosition(LAP_POS);
    m_raceLoc.setPosition(m_lap.getPosition().x + 
		m_lap.getGlobalBounds().width + THIRTY, FIFTY);
    m_timeGame.setPosition(m_raceLoc.getPosition().x +
		m_raceLoc.getGlobalBounds().width + THIRTY, FIFTY);

    printboard();
}

//====================================================
std::string GameStatusBar::timeCalculation(const sf::Time& time)
{
    std::string strTime;

    auto seconds = time.asSeconds() - SIXTY * m_minutes;
    auto millieSeconds = (seconds - int(seconds)) * 100;
    if (seconds < TEN_F)
        strTime = "Time: " + std::to_string(m_minutes) + 
			"'" + "0" + std::to_string(int(seconds)) +
			'"' + std::to_string(int(millieSeconds));
    else
        strTime = "Time: " + std::to_string(m_minutes) + 
			"'" + std::to_string(int(seconds)) + '"' + 
			std::to_string(int(millieSeconds));  //else set it 

    if (seconds > SIXTY)
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