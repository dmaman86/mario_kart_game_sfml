#pragma once
#include "mode7.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Macros.h"
#include "Player.h"
#include "PlayerOnline.h"
#include "MarioKart.h"
#include "State.h"
#include "MapFileCollision.h"
#include "Pipe.h"
#include "UserNetwork.h"

class RaceState : public State
{
public:
	//================ Constructor / Distructor =================
	RaceState(MarioKart::GameDataRef);
	~RaceState() = default;

	//================ Virtual public functions =================
	virtual void Init() override;
	virtual void HandleEvent(const sf::Event&)override;
	virtual void Update(float)override;
	virtual void Draw() override;

private:
	//================ Private functions =========================
	void BuildVecObj();
	void drawStaticObjects();
	void HandleCollision(float deltatime);
	void updateObjLocation();
	void updateDynamic();


	//================ Private members ==========================
	sf::RenderWindow m_window;
	sf::Sprite m_sky;
	Mode7 m_map;
	float m_cameraX, m_cameraY, m_cameraZ, m_theta;
	sf::Clock m_clock;
	MarioKart::GameDataRef m_data;
	Player m_player;
	PlayerOnline m_player2;
	MapFileCollision m_int_map;
	Pipe pipe;
	UserNetwork *m_userJoin;

	sf::Time m_last_update_server;

}; // end RaceState