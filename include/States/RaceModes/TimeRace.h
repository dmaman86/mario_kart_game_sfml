#pragma once

#include "RaceStatesBase.h"
#include <SFML/Graphics.hpp>

class TimeRace : public RaceStatesBase
{
public:
	//================ Constructor / Destructor =================
	TimeRace(MarioKart::GameDataRef&);
	~TimeRace() = default;

	//================ Virtual public functions =================
	void Update(const float) override;
	void Draw() override;

private:
	//================ Private functions =========================
	const bool isFinishTime();
	
	//================ Private members ==========================
	sf::Time m_time_level;
};
