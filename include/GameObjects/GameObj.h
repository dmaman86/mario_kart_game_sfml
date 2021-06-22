#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "Object.h"

class GameObj : public Object, public sf::Drawable, public sf::Transformable {

public:
	GameObj();
	GameObj(const sf::Texture& tex, const sf::Vector2f&, const sf::Vector2f&);
	sf::Vector2f getIntLocation();
	// virtual void draw(sf::RenderWindow& m_window) {if(m_is_active) m_window.draw(m_sprite); }
	void setScale(float x, float y) { m_sprite.setScale(x, y); }
	void setPosition(const sf::Vector2f& );
	void setInAngle(bool b) { m_is_in_angle = b; }
	const bool getIsInAngle()const { return m_is_in_angle; }
	const bool collisionWith(const GameObj& b)const;
    sf::Vector2f& getLocation(){ return *m_location; }
    void setLocation( float x, float y ){ m_location->x = x; m_location->y = y; }
    void setLocation(const sf::Vector2f&  loc){ *m_location = loc; }
    bool getIsActive(){return m_is_active;}
    void setIsActive(bool boo){m_is_active = boo;}
    sf::Sprite& getSprite(){return m_sprite;};
    virtual void updateAnimation(float time){};
	void playSound();

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        states.transform *= getTransform();
        if(m_is_active)
            target.draw(m_sprite);
    }
protected:
	sf::Sprite m_sprite;
	sf::Vector2f *m_location;
	bool m_is_in_angle;
	bool m_is_active;
	sf::Sound m_sound;

};

