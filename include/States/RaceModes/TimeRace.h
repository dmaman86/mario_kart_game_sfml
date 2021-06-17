#pragma once

#include "RaceStatesBase.h"
#include <SFML/Graphics.hpp>

class TimeRace : public RaceStatesBase
{
public:
	//================ Constructor / Destructor =================
	TimeRace(MarioKart::GameDataRef);
	~TimeRace();

	//================ Virtual public functions =================
	void Init() override;
	void HandleEvent(const sf::Event&) override;
	void Update(float) override;
	void Draw() override;

private:
	//================ Private functions =========================
	void finishRase(const bool);
	const bool isFinishTime();
	
	//================ Private members ==========================
	sf::Time m_time_level;
};
