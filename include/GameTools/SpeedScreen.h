#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class SpeedScreen{

public:
	SpeedScreen();
	void Draw(sf::RenderWindow& win, const float force, const float cof);
private:
	std::vector<sf::Sprite> m_speeds_s;

};