#pragma once
#include "SFML/Graphics.hpp"

class SkyLine {

public:
    SkyLine();
	void Update();
	const sf::Sprite& getBack() const { return m_back; }
	const sf::Sprite& getFront() const { return m_front; }

private:
    sf::Sprite m_back;
    sf::Sprite m_front;
};
