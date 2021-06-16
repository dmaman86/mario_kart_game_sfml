#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include "State.h"
#include "StateOfMenu.h"
#include "MarioKart.h"
#include "Button.h"

class CareerState : public StateOfMenu
{
public:
	CareerState(MarioKart::GameDataRef&);
	~CareerState() = default;

	void Init()override;
	void HandleEvent(const sf::Event&) override;
	void Update(float) override;
	void Draw() override;
	void Resume() override;
private:
	bool openLoadFile();
	void resetButtons(size_t);
	std::vector< Button > m_buttons;
	MarioKart::GameDataRef m_data;

};

