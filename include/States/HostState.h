#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <thread>
#include <mutex>
#include <string>

#include "State.h"
#include "MarioKart.h"
#include "Macros.h"
#include "User.h"
#include "Button.h"
#include "CoinRace.h"
#include "TimeRace.h"
#include "DriftKingRace.h"

class HostState : public State
{
public:
    HostState(MarioKart::GameDataRef&);
    HostState(MarioKart::GameDataRef&, const std::string&);
    ~HostState() = default;

    void Init() override;
    void HandleEvent(const sf::Event&) override;
    void Update(float) override;
    void Draw() override;
    void Resume() override;
private:
    struct Map
    {
        std::string map_name;
        sf::RectangleShape m_rect;
        sf::Texture tex;
        sf::Text map_name_tex;
        bool selected;
    };
    using VectorMaps = std::vector<std::shared_ptr<Map>>;

    VectorMaps m_maps;
    sf::Sprite m_background;
    MarioKart::GameDataRef m_data;
    std::shared_ptr<Button> m_back;
    sf::Text m_title;
    sf::Text m_createGame;
    sf::Text m_error;
    sf::Text m_back_state;
    sf::Vector2u m_windowSize;
    std::string m_type_info;

    bool m_validConnection;
    bool m_selected;
    bool m_nextState;
    bool m_createRoom;
    bool m_pressEnter;
    bool m_errorShow;
    float m_effectTime;

    void initTitlesTexts();
    void initErrorsTexts();
    void createMaps(VectorMaps&);
};
