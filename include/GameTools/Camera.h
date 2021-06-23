#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities.h"

class Camera {

public:
	Camera():m_cameraX(0), m_cameraY(0), m_cameraZ(0){}
	
	void InitCamera(const sf::Vector2f& p_pos)
	{
		m_cameraX = p_pos.x * 8;
		m_cameraY = -17;
		m_cameraZ = p_pos.y * 8;
	}
	void setCamera(const sf::Vector2f& p_pos, const float angle, const float y)
	{
		m_cameraX = p_pos.x * 8 - 50 * calcSinDegree(angle);
		m_cameraZ = p_pos.y * 8 + 50 * calcCosDegree(angle);
		m_cameraY = y;
	}

	const float getX()const { return m_cameraX; }
	const float getZ()const { return m_cameraZ; }
	const float getY()const { return m_cameraY; }

private:
	float m_cameraX, m_cameraY, m_cameraZ;

}; //end Camera