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

	void resetButtons(Options);
	void initVectorSprites(const sf::Vector2u&);
	void updateColors(const sf::Vector2f);
	void buyingTest(std::string);
	void initDriver(driver&, const int i, const int j);
	void blockingMyPlayers();
	MarioKart::GameDataRef m_data;
	std::map<std::string, driver> m_drivers;
    std::map<Options, std::shared_ptr<Button>> m_buttons;

    

	std::vector<std::pair<sf::Text, bool >> m_msg;
	std::string m_selectCar;

	sf::Text m_numberCoins;



};


