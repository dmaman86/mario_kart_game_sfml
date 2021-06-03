#pragma once
#include "GameObj.h"
class Player: public GameObj{

public:
    Player();
    Player(const sf::Vector2f , const sf::Vector2f loc);

    void setIntLocation(const sf::Vector2f &loc);
    void setIntLocation(float,int);
    void updateDir();
    void setAngle(float );
    float getAngle();
    //sf::Vector2f m_location;
    float m_angle;
    float m_speed;
    void speedUp();
    void speedDown();
    float getSpeed()const;
};

