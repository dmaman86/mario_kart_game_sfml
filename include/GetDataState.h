#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>

#include "State.h"
#include "MarioKart.h"
#include "Macros.h"
#include "User.h"
#include "Button.h"


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
    sf::Sprite m_background;
    MarioKart::GameDataRef m_data;
    sf::String m_playerInput;
    sf::Text m_playerText;
    sf::Text m_title_get_name;
    std::vector< std::shared_ptr<Button> > m_drivers;
    sf::Sound m_click;
    Button m_save;
    Button m_joinGame;
    Button m_createGame;
    Button m_back;

    const int m_limit = 15;
    bool m_save_data;
    bool m_send_data;
    bool m_nextState;
    float m_effectTime;
    std::string m_user_name;
    std::string m_user_sprite;

    void centerOrigin(sf::Text&);
    void inputLogic(int charTyped);
    void deleteLastChar();
    void initVectorSpritesOnline(const sf::Vector2u&);
    void initVectorSpritesOffline(const sf::Vector2u&);
    void setVolume();
    void resetOtherDrivers(size_t);
};
