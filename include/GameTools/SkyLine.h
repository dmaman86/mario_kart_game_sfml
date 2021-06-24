#pragma once
#include "SFML/Graphics.hpp"

/*
	sky Line:
		The pictures in the back represent the horizon 
*/
class SkyLine {

public:
	//Constructor
    SkyLine(const std::string &);
	
	//Public functions
	void Update(const bool, const float);
	const sf::Sprite& getBack() const { return m_back; }
	const sf::Sprite& getFront() const { return m_front; }

private:
	//Private members
    sf::Sprite m_back;
    sf::Sprite m_front;
};
