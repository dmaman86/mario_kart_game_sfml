#include "Pictures.h"
#include "StaticObject.h"

//============================== Constructor =================================
StaticObject::StaticObject
	(const sf::Texture& tex,const sf::Vector2f &pos) :
		GameObj::GameObj(tex, sf::Vector2f(0,0),pos)
{
}

