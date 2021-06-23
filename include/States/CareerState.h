#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <map>
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
    enum class Options
    {
        NewGame,
        LoadGame,
        Back
    };
    std::map<Options, std::shared_ptr<Button>> m_buttons;
	MarioKart::GameDataRef m_data;

    const bool openLoadFile();
    void resetButtons(Options);
    void updateColors(const sf::Vector2f& loc);
};

