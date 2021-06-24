#include "DriftKingRace.h"
#include "Fonts.h"
#include "Coin.h"

//========================== Constructor / Destructor =========================
DriftKingRace::DriftKingRace(MarioKart::GameDataRef& data) :
	RaceStatesBase(data, data->user.getMapGame())
{
}

//================================= Update =====================================
void DriftKingRace::Update(const float deltatime) {

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
                 m_player.getLap(), Coin::getCollected(), Coin::getCount(), 1);
}

//=============================================================================
const bool DriftKingRace::isFinish()
{
	return m_player.getLap() == 2;
}
