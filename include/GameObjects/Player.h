#pragma once

#include "PlayerBase.h"

class Player : public PlayerBase {

public:
	Player();
	Player(const sf::Vector2f, const sf::Vector2f loc);

	void setIntLocation(const sf::Vector2f& loc);
	void setIntLocation(float, int);
	void updateDir();
	void setAngle(float);
	float getAngle();
	//sf::Vector2f m_location;
	void driveBack();
	void speedUp(float);
	void speedDown(float);
	void updateAcceleration();
	float getSpeed()const;
	void handleLock(float);
	
	float m_force, m_mass, m_acceleration;
	bool m_is_lock;
	sf::Vector2f m_last_pos;
	float m_angle;
	float m_speed;
};

