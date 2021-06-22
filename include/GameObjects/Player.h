#pragma once
#include "Animation.h"
#include "PlayerBase.h"
#include <string>

class FloorAsphalt;
class FloorBrick;
class FloorSand;

class Player : public PlayerBase {

public:
	//================ Constructor / Destructor =================
	Player();
	Player(const sf::Vector2f loc, const sf::Vector2f pos,std::string sprite, bool);
	~Player() = default;

	//================ Virtual public functions =================
	void Update(const float, const int);
	void updateDir();
	void CheckLap(const int);
	void updateAnimation(float time) override;

	void driveBack();
	void spindriver();
	void driveSmaller();
	void SpeedMultiplier();

	void setCoefficientOfFriction(const float cof);
	void setAngle(const float);
	const float getAngle() const { return m_angle; };
	void setLastScorePos(const unsigned int score);
	const int  getLastScorePos()const;
	const float getSpeed()const { return m_force; };
	const bool getIsLoc()const { return m_is_lock; };
	const float getCoefficient()const { return m_coefficient_of_friction; }
	void setFinishLine(float line){m_finish_line = line;}

protected:
	//================ Private functions =========================
	void handleLock(const float);
	virtual void updateSpeed(const float);
	void updateLocation(const float);

	//================ Private members ==========================
    Animation m_animation;
    sf::Clock m_playerClock;
    sf::Vector2f m_last_pos;
    float m_angle;
    float m_coefficient_of_friction;
    float m_force, m_acceleration;
    bool m_is_lock;
    bool m_is_pressed;
    bool m_is_spin;
	bool m_is_smaller;
    int m_last_pos_score;
	float m_smaller_time;
	sf::Time m_timepasses;
	float m_finish_line;
	sf::Sound m_backSound;
	bool m_soundOn;
};

