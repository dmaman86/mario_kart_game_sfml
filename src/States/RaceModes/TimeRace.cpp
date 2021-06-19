#include "TimeRace.h"
#include "Fonts.h"

//========================== Constructor / Destructor =========================
TimeRace::TimeRace(MarioKart::GameDataRef data) : 
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
void TimeRace::finishRase(const bool w_or_l)
{
	m_data->user.updateInGame(false);
	m_data->stateStack.RemoveState();
	sf::Text txt;
	txt.setFont(Fonts::instance().Fonts::getFontMario());
	txt.setPosition(50, 50);
	(w_or_l) ? txt.setString("Win") :
		txt.setString("Lose");

	auto cur_t = m_clock.getElapsedTime().asSeconds();
	while (cur_t + 2.f > m_clock.getElapsedTime().asSeconds())
	{
		m_data->window->clear();
		m_cameraY -= 3;
		RaceStatesBase::Draw();
		RaceStatesBase::UpdateMap();
		m_data->window->draw(txt);
		m_data->window->display();
	}
	//m_build_map_thread.~thread();
}

//=============================================================================
const bool TimeRace::isFinishTime()
{
	return (m_time_level.asSeconds() - m_clock.getElapsedTime().asSeconds()) <= 0;
}
