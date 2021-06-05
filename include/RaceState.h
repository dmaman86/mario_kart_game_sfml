#pragma once
#include "mode7.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Macros.h"
#include "Player.h"
#include "MarioKart.h"
#include "State.h"
#include "MapFileCollision.h"
#include "Pipe.h"
class RaceState : public State
{

public:
	RaceState(MarioKart::GameDataRef);
	~RaceState() = default;
	void run();

	//private function
	virtual void Init() override;
	virtual void HandleEvent(const sf::Event&)override;
	virtual void Update(float)override;
	virtual void Draw() override;


private:
	//private members
	sf::RenderWindow m_window;
	sf::Sprite m_sky;
	Mode7 m_map;
	float m_cameraX, m_cameraY, m_cameraZ, m_theta;
	sf::Clock m_clock;
	MarioKart::GameDataRef m_data;
	Player m_player;
	MapFileCollision m_int_map;
	Pipe pipe;


	//private functions
	void BuildVecObj();
	void drawStaticObjects();
};