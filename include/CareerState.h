#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include "State.h"
#include "MarioKart.h"
#include "UserCareer.h"

class CareerState : public State
{
public:
	CareerState(MarioKart::GameDataRef&);
	~CareerState() = default;

	void Init()override;
	void HandleEvent(const sf::Event&) override;
	void Update(float) override;
	void Draw() override;
private:
	void openLoadFile();
	void setVolume();
	sf::Sprite m_background;
	sf::Sprite m_back;
	sf::Sprite m_new_game;
	sf::Sprite m_load_game;


	UserCareer m_user;
	MarioKart::GameDataRef m_data;

	bool m_backMenu;
	sf::Sound m_click;

};

