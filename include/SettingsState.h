#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "MarioKart.h"
#include "StateOfMenu.h"

class SettingsState : public State
{
public:
    SettingsState(MarioKart::GameDataRef);
    ~SettingsState() = default;


    virtual void Init()override;
    virtual void HandleEvent(const sf::Event&) {};
    virtual void Update(float)override {};
    virtual void Draw()override;

private:
    MarioKart::GameDataRef m_data;
};

