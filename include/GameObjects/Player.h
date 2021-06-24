#pragma once
#include <string>
#include "Animation.h"
#include "PlayerBase.h"
#include "Macros.h"

// Forward declaration
class FloorAsphalt;
class FloorBrick;
class FloorSand;

/*
	Player : 
		manages the image and animation of the driver
		and Player position's in the world
*/
class Player : public PlayerBase {

public:
	//================ Constructor / Destructor ===================
	Player();
	Player(const sf::Vector2f &,const sf::Vector2f & 
			,const std::string& ,const bool);
	~Player() = default;

	//====================== public functions =====================
	void DriveBack();
	void SpinDriver();
	void DriveSmaller();
	void DriveFast() { m_force = PlayerDefinitions::MAX_SPEED; }
	void StopEngineMusic() { m_engine.stop(); }

	//================ Virtual public functions ===================
	void Update(const float, const int);
	void UpdateBreaks();
	void CheckLap(const int);
	void UpdateAnimation(const float time) override;

	// =================== set & get functions ====================
	void setCoefficientOfFriction(const float cof) { m_cof = cof; };
	void setAngle(const float);
	const float getAngle() const { return m_angle; };
	void setLastScorePos(const unsigned int sc) { m_last_pos_score = sc; }
	const int  getLastScorePos()const { return m_last_pos_score; }
	const float getSpeed()const { return m_force; };
	const bool getIsLoc()const { return m_is_lock; };
	const float getCoefficient()const { return m_cof; }
	void setFinishLine(const float line){m_finish_line = line;}
	const bool getIsLock()const { return m_is_lock; }

protected:

	//================ Protected functions =========================
	void HandleLock(const float);
	virtual void UpdateSpeed(const float);
	void UpdateLocation(const float);
	void UpdateDirection(const float);
	void UpdateAcceleration();
	void UpdateSpecialSituations();

	//================ Protected members ===========================
	int m_last_pos_score;
	bool m_is_lock, m_is_pressed, m_is_spin, m_is_smaller, m_soundOn;
	float m_angle, m_force, m_acceleration, m_smaller_time, m_finish_line
		, m_cof; // coefficient of friction
    
	sf::Clock m_playerClock;
    sf::Vector2f m_last_pos;
	sf::Time m_timepasses;
	sf::Music m_engine;
	sf::Sound m_backSound;

	Animation m_animation;

};//end Player

