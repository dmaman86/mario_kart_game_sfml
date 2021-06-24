#include "SpeedScreen.h"
#include "Pictures.h"
#include "Macros.h"

SpeedScreen::SpeedScreen()
{
	for (size_t i = 0; i < 5;i++) {
		sf::Sprite spr(Pictures::instance().getTexture("speed" + std::to_string(i) + ".png"));
		spr.setScale(0.65f, 0.5f);
		spr.setPosition(0, 80);
		m_speeds_s.push_back(spr);
	}
}
//=============================================================================

void SpeedScreen::Draw(sf::RenderWindow& win , const float force, const float cof)
{
	static size_t i = 0;

	if (force >= MAX_SPEED - 2 && cof != 2)
	{
		win.draw(m_speeds_s[(i++) % m_speeds_s.size()]);
	}
}
