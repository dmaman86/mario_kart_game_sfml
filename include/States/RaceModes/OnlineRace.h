#pragma once

#include <thread>
#include <mutex>
#include "PlayerOnline.h"
#include "User.h"
#include "Services.h"
#include "RaceStatesBase.h"

class OnlineRace : public RaceStatesBase
{
public:
	//================ Constructor / Destructor =================
	OnlineRace(MarioKart::GameDataRef&);
	~OnlineRace();

	//================ Virtual public functions =================
	void Init() override;
	void HandleEvent(const sf::Event&) override;
	void Update(float) override;

private:
	//================ Private functions =========================
	void InitNetwork();
	void UpdateNetwork(float);
	void updateDynamic();

	//================ Private members ==========================
	PlayerOnline m_player2;
	User *m_userJoin;
	float m_time_update;
    std::thread m_thread_up;
    std::thread m_thread_get;
    std::mutex m_mutex_player2;
    std::mutex m_mutex_player1;
    Services m_services;
    bool m_finish;
};
