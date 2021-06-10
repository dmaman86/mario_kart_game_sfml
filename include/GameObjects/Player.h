#pragma once
#include "Animation.h"
#include "PlayerBase.h"
#include <string>

class FloorAsphalt;
class FloorBrick;
class FloorSand;

class Player : public PlayerBase {

public:
	Player();
	Player(const sf::Vector2f, const sf::Vector2f loc, std::string id, std::string sprite);

	void setIntLocation(const sf::Vector2f& loc);
	void updateSpeed(float);
	void updateDir();
	void updateLocation(float);
	void setCoefficientOfFriction(const float cof);

	void setAngle(float);
	float getAngle();
	//sf::Vector2f m_location;
	void driveBack();
	void speedUp(float);
	void speedDown(float);
	void updateAcceleration();
	float getSpeed()const;
	void handleLock(float);
	float m_coefficient_of_friction;
	float m_force, m_mass, m_acceleration;
	bool m_is_lock;
	sf::Vector2f m_last_pos;
	float m_angle;
	float m_speed;
	Animation m_animation;
    std::string m_idHost;
    sf::Clock m_playerClock;
    bool m_is_pressed;
};

