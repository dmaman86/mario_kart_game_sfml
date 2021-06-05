#pragma once
#include "StaticObject.h"

class Pipe : public StaticObject{

public:
    Pipe(sf::Vector2f,const sf::Vector2f pos);
	virtual void draw(sf::RenderWindow&)override;
private:
	int m_renderCount;
};


