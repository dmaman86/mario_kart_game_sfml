#include "SkyLine.h"
#include "Pictures.h"
#include "Macros.h"
#include "MacrosGameTools.h"

//================== Conctructor =======================
SkyLine::SkyLine(const std::string& str)
{
	 std::string name = str.substr(0, str.find('.'));
	 auto sb  = name + SKY_B_PNG;
	 auto sf = name + SKY_F_PNG;

	 m_back.setTexture(Pictures::instance().getTexture(sb));
	 m_back.setTextureRect(SKY_LINE_RECT);
	 m_back.setScale(SKY_LINE_SCALE);
	 m_back.setPosition(0, DimensionWindow::HEIGHT / TEN);

	 m_front.setTexture(Pictures::instance().getTexture(sf));
	 m_front.setTextureRect(SKY_LINE_RECT);
	 m_front.setScale(SKY_LINE_SCALE);
	 m_front.setPosition(0, DimensionWindow::HEIGHT / TEN);
}

//=============================================================================
 void SkyLine::Update(const bool lock,const float force)
 {
	 if (!lock && force) {

		 auto s_f = m_front.getTextureRect();
		 auto s_b = m_back.getTextureRect();

		 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		 {
			 s_f.left += TWO;
			 s_b.left += ONE;
		 }
		 else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			 if (s_f.left <= TEN)
			 {
				 s_f.left = MIDDLE_SKY_FRONT;
				 s_b.left = MIDDLE_SKY_BACK;
			 }
			 s_f.left -= TWO;
			 s_b.left -= ONE;
		 }
		 s_f.left %= SIZE_SKY_FRONT;
		 s_b.left %= SIZE_SKY_BACK;

		 m_front.setTextureRect(s_f);
		 m_back.setTextureRect(s_b);
	 }
 }
//=============================================================================
