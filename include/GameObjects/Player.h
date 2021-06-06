#pragma once
#include "GameObj.h"
class Player : public GameObj {

public:
	Player();
	Player(const sf::Vector2f, const sf::Vector2f loc);

	void setIntLocation(const sf::Vector2f& loc);
	void setIntLocation(float, int);
	void updateDir();
	void setAngle(float);
	float getAngle();
	//sf::Vector2f m_location;
	float m_angle;
	float m_speed;
	void speedUp(float);
	void speedDown(float);
	void updateAcceleration();
	float getSpeed()const;
	float m_force, m_mass, m_acceleration;
	bool m_is_lock;
	void handleLock(float);
	sf::Vector2f m_last_pos;
};

