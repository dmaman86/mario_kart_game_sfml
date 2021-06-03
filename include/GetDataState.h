#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "MarioKart.h"

class GetDataState : public State
{
public:
    GetDataState(MarioKart::GameDataRef);
    ~GetDataState() = default;


    void Init() override;
    void HandleEvent(const sf::Event&) override;
    void Update(float) override;
    void Draw() override;
private:
    sf::Sprite m_background;
    MarioKart::GameDataRef m_data;

};
