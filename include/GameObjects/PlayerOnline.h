#pragma once
#include "PlayerBase.h"

/*
	PlayerOnline:
		Represents the other player if the user chooses to play online.
*/
class PlayerOnline : public PlayerBase {

public:
	// Constructor
	PlayerOnline() {};
	PlayerOnline(const std::string & ,const sf::Vector2f&, const sf::Vector2f&);
	
	// public get function
	const sf::Vector2f getLastLocation() { return m_last_location; }

}; // end PlayerOnline

