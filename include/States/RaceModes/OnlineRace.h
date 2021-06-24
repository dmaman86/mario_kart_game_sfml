#pragma once

#include <thread>
#include <mutex>
#include <vector>
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
    void Update(const float) override;

private:
    //================ Private functions =========================
    void InitNetwork();
    void UpdateNetwork(float);
    void updateDynamic();
    void initPositionLikeHost(const std::vector<std::vector <int>>&);
    void initPositionLikeJoin(const std::vector<std::vector <int>>&);
    void finishThread();
    void finishOnline(bool);

    //================ Private members ==========================
    PlayerOnline m_player2;
    User *m_userJoin;
    float m_time_update;
    std::thread m_thread_up;
    std::thread m_thread_get;
    std::mutex m_mutex_player2;
    std::mutex m_mutex_player1;
    bool m_finish;
    const int max_lap = 3;
};
