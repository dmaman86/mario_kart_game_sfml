#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <future>
#include "mode7.h"
#include "Macros.h"
#include "Player.h"
#include "PlayerOnline.h"
#include "MarioKart.h"
#include "State.h"
#include "MapFileCollision.h"
#include "Pipe.h"
#include "UserNetwork.h"
#include "GameStatusBar.h"


class RaceState : public State
{
public:
	//================ Constructor / Destructor =================
	RaceState(MarioKart::GameDataRef);
	~RaceState();

	//================ Virtual public functions =================
	void Init() override;
	void HandleEvent(const sf::Event&) override;
	void Update(float) override;
	void Draw() override;

private:
	//================ Private functions =========================
	void InitNetwork();
	void InitMap();
	void InitSky();
	void UpdateNetwork(float);
	void UpdateMap();
	void UpdatePlayer(float);
	void drawStaticObjects();
	void HandleCollision(float deltatime);
	void updateObjLocation();
	void updateDynamic();
	void updateSky();

	//================ Private members ==========================
	sf::RenderWindow m_window;
	Mode7 m_map;
	float m_cameraX, m_cameraY, m_cameraZ, m_theta;
	sf::Clock m_clock;
	MarioKart::GameDataRef m_data;
	Player m_player;
	PlayerOnline m_player2;
	MapFileCollision m_int_map;
	Pipe pipe;
	UserNetwork *m_userJoin;
	float m_time_update;
    std::string m_map_race;
	GameStatusBar m_status;
    std::future<void> m_response_up;
    std::future<void> m_response_get;
	sf::Sprite m_sky_back;
	sf::Sprite m_sky_front;
}; // end RaceState 