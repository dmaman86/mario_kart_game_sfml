#include "SkyLine.h"
#include "Pictures.h"
#include "Macros.h"

 SkyLine::SkyLine() {
	 m_back.setTexture(Pictures::instance().getTexture(Pictures::sky_back));
	 m_back.setTextureRect(sf::Rect(0, 0, 300, 32));
	 m_back.setScale(4, 4);
	 m_back.setPosition(0, HIGHT / 10);

	 m_front.setTexture(Pictures::instance().getTexture(Pictures::sky_front));
	 m_front.setTextureRect(sf::Rect(0, 0, 300, 32));
	 m_front.setScale(4, 4);
	 m_front.setPosition(0, HIGHT / 10);
}

 void SkyLine::Update()
 {
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
