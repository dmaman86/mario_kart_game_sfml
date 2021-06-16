#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include "State.h"
#include "StateOfMenu.h"
#include "MarioKart.h"
#include "UserCareer.h"

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
	void openLoadFile();
	/*sf::Sprite m_new_game;
	sf::Sprite m_load_game;*/
	using Pair = std::pair< sf::Sprite, bool >;
	std::vector< Pair > m_buttons;

	UserCareer m_user;
	MarioKart::GameDataRef m_data;

};

