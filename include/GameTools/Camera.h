#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities.h"

class Camera {

public:
	Camera():m_cameraX(0), m_cameraY(0), m_cameraZ(0){}
	
	void InitCamera(const sf::Vector2f& p_pos);
	void setCamera(const sf::Vector2f& p_pos, const float angle, const float y);

	const float getX()const { return m_cameraX; }
	const float getZ()const { return m_cameraZ; }
	const float getY()const { return m_cameraY; }

private:
	float m_cameraX, m_cameraY, m_cameraZ;

}; //end Camera