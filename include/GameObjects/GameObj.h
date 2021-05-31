#pragma once
#include "SFML/Graphics.hpp"

class GameObj {

public:
    GameObj();
    GameObj(const sf::Texture &tex, const sf::Vector2f );
    void draw(sf::RenderWindow& m_window){m_window.draw(m_sprite);}

protected:
    sf::Sprite m_sprite;


};

