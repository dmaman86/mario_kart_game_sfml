#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include <map>
#include <memory>
#include <functional>

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
    // constructor & destructor
    HostState(MarioKart::GameDataRef&);
    HostState(MarioKart::GameDataRef&, const std::string&);
    ~HostState() = default;
    // virtual functions
    void Init() override;
    void HandleEvent(const sf::Event&) override;
    void Update(const float) override;
    void Draw() override;
    void Resume() override;
private:
    // private members
    typedef std::function<void()> NextState;
    enum class MapNames
    {
        RainBow,
        Donut,
        Ghost
    };
    struct Map
    {
        std::string map_name;
        sf::RectangleShape m_rect;
        sf::Texture tex;
        sf::Text map_name_tex;
        bool selected;
    };
    using Maps = std::map<MapNames, std::shared_ptr<Map>>;
    using OptionOffline = std::map<std::string, NextState>;

    Maps m_maps;
    OptionOffline m_options_offline;
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

    // private functions
    void initTitlesTexts();
    void initErrorsTexts();
    void createMaps();
    void initTexture(sf::Texture&, const std::string&);
    void initRectangleShape(sf::RectangleShape&, sf::Texture&, size_t);
    void initText(sf::Text&, size_t, const sf::RectangleShape&);
    void resetOutLineColor(MapNames);
    void initOptionsOffline();
};
