#include "SpeedScreen.h"
#include "Pictures.h"
#include "Macros.h"
#include "MacrosGameTools.h"

//============================== Constructor ==================================
SpeedScreen::SpeedScreen()
{
	for (auto i = 0; i < SPEED_SCREEN_SIZE;i++) {
		sf::Sprite spr(Pictures::instance().getTexture("speed" + std::to_string(i) + ".png"));
		spr.setScale(SPEED_SCREEN_SCALE);
		spr.setPosition(SPEED_SCREEN_POS);
		m_speeds_s.push_back(spr);
	}
}

//=============================================================================
void SpeedScreen::Draw(sf::RenderWindow& win , const float force, const float cof)
{
	static size_t i = 0;

	if (force >= PlayerDefinitions::MAX_SPEED - TWO && cof != TWO)
		win.draw(m_speeds_s[(i++) % m_speeds_s.size()]);
}
