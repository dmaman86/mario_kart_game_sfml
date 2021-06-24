#include "Camera.h"

void Camera::InitCamera(const sf::Vector2f& p_pos)
{
	m_cameraX = p_pos.x * 8;
	m_cameraY = -17;
	m_cameraZ = p_pos.y * 8;
}

void Camera::setCamera(const sf::Vector2f& p_pos, const float angle, const float y)
{
	m_cameraX = p_pos.x * 8 - 50 * calcSinDegree(angle);
	m_cameraZ = p_pos.y * 8 + 50 * calcCosDegree(angle);
	m_cameraY = y;
}
