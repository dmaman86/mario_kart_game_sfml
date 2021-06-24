#include "Pictures.h"
#include "StaticObject.h"

//============================== Constructor =================================
StaticObject::StaticObject
	(const sf::Texture& tex) :
		GameObj::GameObj(tex, sf::Vector2f(0,0), sf::Vector2f(0, 0))
{
}

