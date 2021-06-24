#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <future>
#include <thread>
#include <mutex>
#include "mode7.h"
#include "Macros.h"
#include "Player.h"
#include "MarioKart.h"
#include "State.h"
#include "Board.h"
#include "Pipe.h"
#include "User.h"
#include "GameStatusBar.h"
#include "Services.h"
#include <thread>
#include "SkyLine.h"
#include "SpeedScreen.h"

class RaceStatesBase : public State
{
public:
    //================ Constructor / Destructor =================
    RaceStatesBase(MarioKart::GameDataRef&,const std::string& );
    ~RaceStatesBase() = default;

    //================ Virtual public functions =================
    void Init() override;
    void HandleEvent(const sf::Event&) override;
    void Update(const float) override;
    void Draw() override;
    void UpdateAnimation(const float time);


protected:
    //================ Private functions =========================
    void InitMap();
	void InitPlayerLoc();
    void InitSky();
    void UpdateMap();
    void UpdatePlayer(float);
    void drawStaticObjects();
    void HandleCollision();
    bool correctDirection();
    void startRaceScreen();
	void finishRase(const bool);
    //================ Private members ==========================
    Mode7 m_map;
	Camera m_camera;
	MarioKart::GameDataRef m_data;
    Player m_player;
    Board m_board;
	GameStatusBar m_status;
	SkyLine m_sky;
	SpeedScreen m_speed_scr;
	float m_cameraY;
	std::string m_map_race;
	std::thread m_build_map_thread;
	sf::Clock m_clock;
	sf::Sprite m_background;
	sf::Sprite m_game_boy;
	sf::View m_view;
	bool m_first;
    sf::Music m_musicMap;
	sf::Sound m_win_s;
	sf::Sound m_lose_s;

}; //end RaceStateBase