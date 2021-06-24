#include "TimeRace.h"
#include "Fonts.h"
#include "Coin.h"
#include "MacrosRaceModes.h"
//========================== Constructor / Destructor =========================
TimeRace::TimeRace(MarioKart::GameDataRef& data) : 
	RaceStatesBase(data, data->user.getMapGame())
	, m_time_level(sf::seconds(TIME_RACE))
{
}

//================================= Update =====================================
void TimeRace::Update(const float deltatime) {

	try {
		RaceStatesBase::Update(deltatime);

		if (isFinishTime())
		{
			finishRase(false);
		}

		if (m_player.getLap() == 2)
		{
			auto add_points = (m_time_level.asSeconds() - 
				m_clock.getElapsedTime().asSeconds()) * HUNDRED;
			m_data->user.setCoins(int(add_points) + m_data->user.getCoins());
			finishRase(true);
		}
	}
	catch (...) {
		finishRase(false);
	}
}

//=============================================================================
void TimeRace::Draw()
{
	RaceStatesBase::Draw();
	m_status.printGameStatus
	(sf::seconds(m_time_level.asSeconds() -
		m_clock.getElapsedTime().asSeconds()),
		m_player.getLap(), Coin::getCollected(), Coin::getCount(), 2);
}

//=============================================================================
const bool TimeRace::isFinishTime()
{
	return (m_time_level.asSeconds() - m_clock.getElapsedTime().asSeconds()) <= 0;
}
