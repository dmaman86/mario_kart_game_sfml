#pragma once

#include "SFML/Graphics.hpp"
#include "Object.h"

class GameObj : public Object {

public:
	GameObj();
	GameObj(const sf::Texture& tex, const sf::Vector2f, const sf::Vector2f);
	sf::Vector2f getIntLocation();
	virtual void draw(sf::RenderWindow& m_window) {if(m_is_active) m_window.draw(m_sprite); }
	void setScale(float x, float y) { m_sprite.setScale(x, y); }
	void setPosition(sf::Vector2f);
	void setInAngle(bool b) { m_is_in_angle = b; }
	const bool getIsInAngle()const { return m_is_in_angle; }
	const bool collisionWith(const GameObj& b)const;
    sf::Vector2f& getLocation(){ return m_location; }
    bool getIsActive(){return m_is_active;}
    void setIsActive(bool boo){m_is_active = boo;}
protected:
	sf::Sprite m_sprite;
	sf::Vector2f m_location;
	bool m_is_in_angle;
	bool m_is_active;
};

