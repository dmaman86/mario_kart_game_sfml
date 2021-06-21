#include "CoinRace.h"
#include "Fonts.h"
#include "Coin.h"

//========================== Constructor / Destructor =========================
CoinRace::CoinRace(MarioKart::GameDataRef& data) :
	RaceStatesBase(data, data->user.getMapGame())
{
}

//=============================================================================
CoinRace::~CoinRace()
{
}

//================================= Update =====================================
void CoinRace::Update(float deltatime) {


	RaceStatesBase::Update(deltatime);
	m_player.updateAnimation(deltatime);
	if (isFinish())
	{
		auto add_points = Coin::getCount()*50 / m_clock.getElapsedTime().asSeconds();
		m_data->user.setCoins(int(add_points) + m_data->user.getCoins());
		finishRase(true);
	}
}

//=============================================================================
void CoinRace::Draw()
{
	RaceStatesBase::Draw();
	m_status.printGameStatus
	(sf::seconds(m_clock.getElapsedTime().asSeconds()),
		m_player.getLap(), 0, 0, correctDirection());
}

//=============================================================================
void CoinRace::finishRase(const bool w_or_l)
{
	m_data->user.updateInGame(false);
	m_data->stateStack.RemoveState();
	sf::Text txt;
	txt.setFont(Fonts::instance().Fonts::getFontMario());
	txt.setPosition(50, 50);
	(w_or_l) ? txt.setString("Win") :
		txt.setString("Lose");

	auto cur_t = m_clock.getElapsedTime().asSeconds();
	while (cur_t + 1.5f > m_clock.getElapsedTime().asSeconds())
	{
		m_data->window->clear();
		m_cameraY -= 3;
		RaceStatesBase::Draw();
		RaceStatesBase::UpdateMap();
		m_data->window->draw(txt);
		m_data->window->display();
	}
}

//=============================================================================
const bool CoinRace::isFinish()
{
	return (Coin::getCount() - Coin::getCollected()) <= 0;
}
