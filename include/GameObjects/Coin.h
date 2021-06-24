#pragma once
#include "StaticObject.h"
#include <iostream>
#include "Animation.h"

//Coin
class Coin : public StaticObject {

public:
	//================ Constructor / Destructor ==================
	Coin();
	~Coin();

	//================= Public functions =========================
	void addCollected() { m_num_collected++; }
	void UpdateAnimation(const float time) override 
		{ m_animation.update(time, true); }
	
	//================= static get functions =====================
	static const int getCount() { return m_num_coins; }
	static const int getCollected() { return m_num_collected; }

private:
	static int m_num_coins; // all coin in the level
	static int m_num_collected; // coin that collected
    Animation m_animation;

};//end Coin 



