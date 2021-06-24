#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities.h"

/*
	Represents the camera in the game located just behind the player
*/
class Camera {

public:
	Camera():m_cameraX(0), m_cameraY(0), m_cameraZ(0){}
	~Camera() = default;
	//public functions
	void InitCamera(const sf::Vector2f& p_pos);
	void setCamera(const sf::Vector2f& p_pos, const float angle, const float y);
	//get functions
	const float getX()const { return m_cameraX; }
	const float getZ()const { return m_cameraZ; }
	const float getY()const { return m_cameraY; }

private:
	//private members
	float m_cameraX, m_cameraY, m_cameraZ;

}; //end Camera