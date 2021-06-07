#pragma once
#include "GameObj.h"

class PlayerBase : public GameObj {

public:
	PlayerBase() {};
	PlayerBase(const sf::Texture&, const sf::Vector2f pos, const sf::Vector2f loc);

protected:

};

