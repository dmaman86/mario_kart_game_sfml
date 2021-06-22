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
	try {

		RaceStatesBase::Draw();
        m_status.printGameStatus
                (sf::seconds(m_clock.getElapsedTime().asSeconds()),
                 m_player.getLap(), Coin::getCollected(), Coin::getCount(), 0);
	}
	catch (...)
	{
		finishRase(false);
	}
}

//=============================================================================
const bool CoinRace::isFinish()
{
	return (Coin::getCount() - Coin::getCollected()) <= 0;
}
