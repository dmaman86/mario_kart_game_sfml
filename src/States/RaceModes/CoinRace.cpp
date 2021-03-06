#include "CoinRace.h"
#include "Fonts.h"
#include "Coin.h"
#include "MacrosRaceModes.h"

//========================== Constructor / Destructor =========================
CoinRace::CoinRace(MarioKart::GameDataRef& data) :
	RaceStatesBase(data, data->user.getMapGame())
{
}

//================================= Update =====================================
void CoinRace::Update(const float deltatime) {
	
	try {
		RaceStatesBase::Update(deltatime);
		m_player.UpdateAnimation(deltatime);
		if (isFinish())
		{
			auto add_points = Coin::getCount() * THOUSAND / m_clock.getElapsedTime().asSeconds();
			m_data->user.setCoins(int(add_points) + m_data->user.getCoins());
			finishRase(true);
		}
	}
	catch (...) {
		finishRase(false);
	}
}

//=============================================================================
void CoinRace::Draw()
{
	RaceStatesBase::Draw();
	m_status.printGameStatus
	(sf::seconds(m_clock.getElapsedTime().asSeconds()),
		m_player.getLap(), Coin::getCollected(), Coin::getCount(), 0);
}

//=============================================================================
const bool CoinRace::isFinish()
{
	return (Coin::getCount() - Coin::getCollected()) <= 0;
}
