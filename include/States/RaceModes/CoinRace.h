#pragma once

#include "RaceStatesBase.h"
#include <SFML/Graphics.hpp>

class CoinRace : public RaceStatesBase
{
public:
	//================ Constructor / Destructor =================
	CoinRace(MarioKart::GameDataRef&);
	~CoinRace() = default;

	//================ Virtual public functions =================

	void Update(const float) override;
	void Draw() override;

private:
	//================ Private functions =========================
	const bool isFinish();

	//================ Private members ==========================
};
