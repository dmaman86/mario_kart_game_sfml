#pragma once
#include "SFML/Graphics.hpp"

class GameObj {

public:
    GameObj();
    GameObj(const sf::Texture &tex, const sf::Vector2f ,const sf::Vector2f);
    sf::Vector2f getIntLocation();
    void draw(sf::RenderWindow& m_window){m_window.draw(m_sprite);}
    void setScale(float x,float y){m_sprite.setScale(x,y );}
    void setPosition(sf::Vector2f);
    void setInAngle(bool b){m_is_in_angle = b;}
    const bool getIsInAngle(){return m_is_in_angle;}
protected:
    sf::Sprite m_sprite;
    sf::Vector2f m_location;
    bool m_is_in_angle;
};

