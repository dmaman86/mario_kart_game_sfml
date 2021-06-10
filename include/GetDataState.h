#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>

#include "State.h"
#include "MarioKart.h"
#include "Macros.h"
#include "UserNetwork.h"


class GetDataState : public State
{
public:
    GetDataState(MarioKart::GameDataRef&);
    ~GetDataState() = default;

    void Init() override;
    void HandleEvent(const sf::Event&) override;
    void Update(float) override;
    void Draw() override;
    void Resume() override;
private:
    using Pair = std::pair< std::string, sf::Sprite>;

    sf::Sprite m_background;
    MarioKart::GameDataRef m_data;
    sf::String m_playerInput;
    sf::Sprite m_back;
    sf::Text m_playerText;
    sf::Text m_title_get_name;
    sf::Text m_save;
    sf::Text m_hostGame;
    sf::Text m_joinGame;
    std::vector< Pair > m_drivers;
    sf::Sound m_click;

    const int m_limit = 15;
    bool m_save_data;
    bool m_send_data;
    bool m_hostPressed;
    bool m_joinPressed;
    bool m_nextState;
    float m_effectTime;
    bool m_backMenu;
    std::string m_user_name;
    std::string m_user_sprite;

    void centerOrigin(sf::Text&);
    void inputLogic(int charTyped);
    void deleteLastChar();
    void initVectorSprites(const sf::Vector2u&);
    void setVolume();
};
