#include "TimeRace.h"
#include "Fonts.h"

//========================== Constructor / Destructor =========================
TimeRace::TimeRace(MarioKart::GameDataRef& data) : 
	RaceStatesBase(data, data->user.getMapGame())
	, m_time_level(sf::seconds(50))
{
}

//=============================================================================
TimeRace::~TimeRace()
{
}

//================================= Update =====================================
void TimeRace::Update(float deltatime) {

	RaceStatesBase::Update(deltatime);
	
	if (isFinishTime())
	{
		finishRase(false);
	}

	if (m_player.getLap() == 2)
	{
		auto add_points = m_time_level.asSeconds() - m_clock.getElapsedTime().asSeconds();
		m_data->user.setCoins(int(add_points)+ m_data->user.getCoins());
		finishRase(true);
	}
}

//=============================================================================
void TimeRace::Draw()
{
	RaceStatesBase::Draw();
	m_status.printGameStatus
		(sf::seconds(m_time_level.asSeconds() - 
			m_clock.getElapsedTime().asSeconds()),
			m_player.getLap(), 0, 0, correctDirection());
}

//=============================================================================
const bool TimeRace::isFinishTime()
{
	return (m_time_level.asSeconds() - m_clock.getElapsedTime().asSeconds()) <= 0;
}
