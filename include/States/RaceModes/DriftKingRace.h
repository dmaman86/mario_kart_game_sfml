#pragma once

#include "RaceStatesBase.h"
#include <SFML/Graphics.hpp>

class DriftKingRace : public RaceStatesBase
{
public:
	//================ Constructor / Destructor =================
	DriftKingRace(MarioKart::GameDataRef);
	~DriftKingRace();

	//================ Virtual public functions =================

	void Update(float) override;
	void Draw() override;

private:
	//================ Private functions =========================
	void finishRase(const bool);
	const bool isFinish();

	//================ Private members ==========================
};
