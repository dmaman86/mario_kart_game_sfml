#pragma once
#include "PlayerBase.h"

class PlayerOnline : public PlayerBase {

public:

	PlayerOnline() {};
	PlayerOnline(const sf::Texture& ,const sf::Vector2f, const sf::Vector2f);
	
	void updateLastLocation() { 
		m_last_location = m_location;
		m_location.x -= 0.5;
		m_location.y -= 0.5;
	}
	const sf::Vector2f getLastLocation() { return m_last_location; }

protected:

	sf::Vector2f m_last_location;
};

