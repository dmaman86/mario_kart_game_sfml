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
	Player(const sf::Vector2f loc, const sf::Vector2f pos,std::string sprite);
	virtual void draw(sf::RenderWindow& m_window) override;
	void updateSpeed(float);
	void updateDir();
	void updateLocation(float);
	void setCoefficientOfFriction(const float cof);
    void spindriver();
	void driveSmaller();
	void setAngle(float);
	float getAngle();
    void driveBack();
	float getSpeed()const;
	void handleLock(float);
	void updateAnimation();
	void setLastScorePos(unsigned int score);
     int getLastScorePos()const;
    void addLap(){++m_lap;}
    int getLap(){return m_lap;}


private:

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
    int m_lap;
	float m_smaller_time;
	std::vector<sf::Sprite> m_speeds_s; 
};

