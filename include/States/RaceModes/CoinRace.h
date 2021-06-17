#pragma once

#include "RaceStatesBase.h"
#include <SFML/Graphics.hpp>

class CoinRace : public RaceStatesBase
{
public:
	//================ Constructor / Destructor =================
	CoinRace(MarioKart::GameDataRef);
	~CoinRace();

	//================ Virtual public functions =================

	void Update(float) override;
	void Draw() override;

private:
	//================ Private functions =========================
	void finishRase(const bool);
	const bool isFinish();

	//================ Private members ==========================
};
