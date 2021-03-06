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

	//===================public function=================
	void Init() override;
	void HandleEvent(const sf::Event&) override;
	void Update(const float) override;
	void Draw() override;

private:
	//===================private members=================
	struct driver
	{
	public:
		driver(bool a, std::string b, sf::Text c) :buy(a), sprite(b), price(c) {};
		bool buy;
		Button sprite;
		sf::Text price;
	};

    enum class Options
    {
        Back,
		WantToBuy,
		successfully,
		EnoughMoney,

    };

	//===================private function=================
	void resetButtons(Options);
	void initVectorSprites();
	void updateColors(const sf::Vector2f);
	void buyingTest(std::string);
	void initDriver(driver&, const int i);
	void blockingMyPlayers();
	void createText(const sf::Vector2u);


	//===================private members=================
	MarioKart::GameDataRef m_data;
	std::map<std::string, driver> m_drivers;
    std::map<Options, std::shared_ptr<Button>> m_buttons;
	std::vector<std::pair<sf::Text, bool >> m_msg;
	std::string m_selectCar;
	sf::Text m_numberCoins;
	sf::Text m_title;



};


