#include "SkyLine.h"
#include "Pictures.h"
#include "Macros.h"

 SkyLine::SkyLine(const std::string str) {

	 std::string name = str.substr(0, str.find('.'));
	 auto sb  = name + "_sky_back.png";
	 auto sf = name + "_sky_front.png";

	 m_back.setTexture(Pictures::instance().getTexture(sb));
	 m_back.setTextureRect(sf::Rect(0, 0, 300, 32));
	 m_back.setScale(4, 4);
	 m_back.setPosition(0, HIGHT / 10);

	 m_front.setTexture(Pictures::instance().getTexture(sf));
	 m_front.setTextureRect(sf::Rect(0, 0, 300, 32));
	 m_front.setScale(4, 4);
	 m_front.setPosition(0, HIGHT / 10);
}

 void SkyLine::Update(const bool lock,const float force)
 {
	 if (!lock && force) {

		 auto x = m_front.getTextureRect();
		 auto y = m_back.getTextureRect();

		 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		 {
			 x.left += 2;
			 y.left += 1;
		 }
		 else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			 if (x.left <= 10)
			 {
				 x.left = 1040;
				 y.left = 485;
			 }
			 x.left -= 2;
			 y.left -= 1;
		 }
		 x.left %= 2560;
		 y.left %= 1536;

		 m_front.setTextureRect(x);
		 m_back.setTextureRect(y);
	 }
 }
