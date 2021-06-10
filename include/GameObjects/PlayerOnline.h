#pragma once
#include "PlayerBase.h"

class PlayerOnline : public PlayerBase {

public:

	PlayerOnline() {};
	PlayerOnline(const std::string ,const sf::Vector2f, const sf::Vector2f);
	
	void updateLastLocation() { 
		m_last_location = m_location;
	}
	const sf::Vector2f getLastLocation() { return m_last_location; }

protected:

	sf::Vector2f m_last_location;
};

