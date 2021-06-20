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
#include "PlayerOnline.h"
#include <thread>

class RaceStatesBase : public State
{
public:
    //================ Constructor / Destructor =================
    RaceStatesBase(MarioKart::GameDataRef);
    RaceStatesBase(MarioKart::GameDataRef,const std::string& );

    ~RaceStatesBase();

    //================ Virtual public functions =================
    void Init() override;
    void HandleEvent(const sf::Event&) override;
    void Update(float) override;
    void Draw() override;

protected:
    //================ Private functions =========================
    void InitMap();
    void InitSky();
    void UpdateMap();
    void UpdatePlayer(float);
    void drawStaticObjects();
    void HandleCollision(float deltatime);
    void updateSky();
    bool correctDirection();
    void startRaceScreen();
    //================ Private members ==========================
	PlayerOnline m_player2;
    Mode7 m_map;
	Camera m_camera;

	float m_cameraX, m_cameraY, m_cameraZ;

    sf::Clock m_clock;
    MarioKart::GameDataRef m_data;
    Player m_player;
    Board m_board;
    std::string m_map_race;
    GameStatusBar m_status;
    sf::Sprite m_sky_back;
    sf::Sprite m_sky_front;
	sf::Sprite m_game_boy;
    std::thread m_build_map_thread;
	sf::View m_view;

}; //end RaceStateBase