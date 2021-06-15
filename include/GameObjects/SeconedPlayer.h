#pragma once
#include "Player.h"


class SeconedPlayer : public Player{
public:
        SeconedPlayer()= default;;
        SeconedPlayer(const sf::Vector2f loc, const sf::Vector2f pos,std::string sprite);

        void updateSpeed(const float) override;
    const sf::Vector2f getLastLocation() { return m_last_location; }
};


