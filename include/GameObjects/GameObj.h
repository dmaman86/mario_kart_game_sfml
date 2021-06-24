#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "Object.h"
#include "MacrosGameObj.h"

/*
	GameObj : The basis of all objects in the game
*/
class GameObj : public Object, public sf::Drawable, public sf::Transformable {

public:

	//================ Constructor / Destructor ==================
	GameObj();
	GameObj(const sf::Texture& tex, const sf::Vector2f&, const sf::Vector2f&);
	virtual ~GameObj() = default;
	
	//================= Public functions =========================
	const bool collisionWith(const GameObj& b)const;
	void playSound() { this->m_sound.play(); }
	virtual void UpdateAnimation(const float) {};

	//================= get & set functions ======================
	void setScale(float x, float y) { m_sprite.setScale(x, y); }
	void setPosition(const sf::Vector2f& pos) { m_sprite.setPosition(pos); }
	void setInAngle(bool b) { m_is_in_angle = b; }
	const bool getIsInAngle()const { return m_is_in_angle; }
	const sf::Vector2f getLocation()const { return m_location; }
	void setLocation(const float x, const float y);
    void setLocation(const sf::Vector2f&  loc){ m_location = loc; }
	const bool getIsActive()const {return m_is_active;}
    void setIsActive(bool boo){m_is_active = boo;}
    const sf::Sprite& getSprite()const{return m_sprite;};

protected:

	// protected members
	sf::Sprite m_sprite;
	sf::Vector2f m_location;
	bool m_is_in_angle;
	bool m_is_active;
	sf::Sound m_sound;

private:

	//================= Private functions =========================
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};// end GameObj

