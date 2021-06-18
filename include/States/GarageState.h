#pragma once

#include"StateOfMenu.h"
#include "Button.h"
#include <vector>
#include <algorithm>
#include <map>


class GarageState :public StateOfMenu
{
public:
	GarageState(MarioKart::GameDataRef&);
	~GarageState() = default;


	void Init() override;
	void HandleEvent(const sf::Event&) override;
	void Update(float) override;
	void Draw() override;

private:
    enum class Options
    {
        Back
    };

	MarioKart::GameDataRef m_data;
	std::vector<std::pair< Button, sf::Text>> m_drivers;
    std::map<Options, std::shared_ptr<Button>> m_buttons;

    void resetButtons(Options);
    void initVectorSprites(const sf::Vector2u&);
};
