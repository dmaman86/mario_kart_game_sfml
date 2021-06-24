#pragma once

#include "RaceStatesBase.h"
#include <SFML/Graphics.hpp>

class DriftKingRace : public RaceStatesBase
{
public:
	//================ Constructor / Destructor =================
	DriftKingRace(MarioKart::GameDataRef&);
	~DriftKingRace() = default;

	//================ Virtual public functions =================

	void Update(const float) override;
	void Draw() override;

private:
	//================ Private functions =========================
	const bool isFinish();

	//================ Private members ==========================
};
