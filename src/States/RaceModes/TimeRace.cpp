#include "TimeRace.h"

//========================== Constructor / Destructor =========================
TimeRace::TimeRace(MarioKart::GameDataRef data) : 
	RaceStatesBase(data, data->user.getMapGame())
	, m_time_level(sf::seconds(5))
{
}

//=============================================================================
TimeRace::~TimeRace()
{
}

//========================= Init section ======================================
void TimeRace::Init()
{
	RaceStatesBase::Init();
}

//=============================================================================
void TimeRace::HandleEvent(const sf::Event& ev)
{
	RaceStatesBase::HandleEvent(ev);
}

//================================= Update =====================================
void TimeRace::Update(float deltatime) {

	RaceStatesBase::Update(deltatime);
	
	if(isFinish())
		finishRase();
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
void TimeRace::finishRase()
{
	m_data->user.updateInGame(false);
	m_data->stateStack.RemoveState();
}

//=============================================================================
const bool TimeRace::isFinish()
{
	return (m_time_level.asSeconds() - m_clock.getElapsedTime().asSeconds()) <= 0;
}
