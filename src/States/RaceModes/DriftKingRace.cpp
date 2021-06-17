#include "DriftKingRace.h"
#include "Fonts.h"

//========================== Constructor / Destructor =========================
DriftKingRace::DriftKingRace(MarioKart::GameDataRef data) :
	RaceStatesBase(data, data->user.getMapGame())
{
}

//=============================================================================
DriftKingRace::~DriftKingRace()
{
}

//================================= Update =====================================
void DriftKingRace::Update(float deltatime) {

	RaceStatesBase::Update(deltatime);

	if (isFinish())
	{
		auto add_points = 1000 - m_clock.getElapsedTime().asSeconds();
		m_data->user.setCoins(int(add_points) + m_data->user.getCoins());
		finishRase(true);
	}
	else if(m_player.getCoefficient() != 1)
		finishRase(false);
}

//=============================================================================
void DriftKingRace::Draw()
{
	RaceStatesBase::Draw();
	m_status.printGameStatus
	(sf::seconds(m_clock.getElapsedTime().asSeconds()),
		m_player.getLap(), 0, 0, correctDirection());
}

//=============================================================================
void DriftKingRace::finishRase(const bool w_or_l)
{
	m_data->user.updateInGame(false);
	m_data->stateStack.RemoveState();
	sf::Text txt;
	txt.setFont(Fonts::instance().Fonts::getFontMario());
	txt.setPosition(50, 50);
	(w_or_l) ? txt.setString("Win") :
		txt.setString("Lose");

	auto cur_t = m_clock.getElapsedTime().asSeconds();
	while (cur_t + 3.f > m_clock.getElapsedTime().asSeconds())
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
const bool DriftKingRace::isFinish()
{
	return m_player.getLap() == 2;
}
