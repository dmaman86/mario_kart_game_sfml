#pragma once
#include "StaticObject.h"
#include <iostream>
#include "Animation.h"
class Coin : public StaticObject {

public:
	Coin(sf::Vector2f, const sf::Vector2f pos);
	~Coin();

	void addCollected() { m_num_collected++; }

	// static function
	static const int getCount();
	static const int getCollected();
    void updateAnimation(float time) override;


private:
	static int m_num_coins; // all coin in the level
	static int m_num_collected; // coin that collected
    Animation m_animation;
};



