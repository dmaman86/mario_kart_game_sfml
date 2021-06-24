#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

/*
SpeedScreen:
	Pictures alternate on the screen as the player drive fast
*/
class SpeedScreen{

public:
	//Constructor/Destructor
	SpeedScreen();
	~SpeedScreen() = default;
	//Public functions
	void Draw(sf::RenderWindow& win, const float force, const float cof);
private:
	//private members
	std::vector<sf::Sprite> m_speeds_s;

};//end SpeedScreen