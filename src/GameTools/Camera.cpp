#include "Camera.h"
#include "MacrosGameTools.h"

// Starting with the player
//=============================================================================
void Camera::InitCamera(const sf::Vector2f& p_pos)
{
	m_cameraX = p_pos.x * SCREEN_TO_2D;
	m_cameraY = CAMERA_HEIGHT;
	m_cameraZ = p_pos.y * SCREEN_TO_2D;
}

//=============================================================================
void Camera::setCamera(const sf::Vector2f& p_pos, const float angle, const float y)
{
	m_cameraX = p_pos.x * SCREEN_TO_2D - DIS_TO_PLAYER * calcSinDegree(angle);
	m_cameraZ = p_pos.y * SCREEN_TO_2D + DIS_TO_PLAYER * calcCosDegree(angle);
	m_cameraY = y;
}