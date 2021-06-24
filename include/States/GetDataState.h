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
    // constructor & destructor
    GetDataState(MarioKart::GameDataRef&);
    ~GetDataState() = default;
    // virtual functions
    void Init() override;
    void HandleEvent(const sf::Event&) override;
    void Update(const float) override;
    void Draw() override;
    void Resume() override;
private:
    // private members
    sf::Sprite m_background;
    MarioKart::GameDataRef m_data;
    sf::String m_playerInput;
    sf::Text m_playerText;
    sf::Text m_title_get_name;
    sf::Text m_choose_drive;
    sf::Text m_error;
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
    bool m_errorShow;
    float m_effectTime;
    std::string m_user_name;
    std::string m_user_sprite;

    // private functions
    void centerOrigin(sf::Text&);
    void inputLogic(int charTyped);
    void deleteLastChar();
    void initVectorSpritesOnline(const sf::Vector2u&);
    void initVectorSpritesOffline(const sf::Vector2u&);
    void setVolume();
    void resetOtherDrivers(size_t);
    void initTexts(const sf::Vector2u&);
    void initText(sf::Text&, const std::string&, const sf::Color&);
};
