#pragma once
#include"StateOfMenu.h"
#include "Button.h"
#include <vector>
#include <algorithm>


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
	void resetButtons(size_t);
	void initVectorSprites(const sf::Vector2u&);


	

	MarioKart::GameDataRef m_data;
	std::vector<std::pair< Button, sf::Text>> m_drivers;
	std::vector< Button > m_buttons;
};
