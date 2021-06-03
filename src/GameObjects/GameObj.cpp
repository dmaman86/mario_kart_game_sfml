
#include <iostream>
#include "GameObj.h"

GameObj::GameObj(const sf::Texture &tex, const sf::Vector2f loc,const sf::Vector2f pos) : m_location(pos),m_is_in_angle(false){
    m_sprite.setTexture(tex);
    m_sprite.setPosition(loc);

}

GameObj::GameObj() {

}

void GameObj::setPosition(sf::Vector2f loc) {
  m_sprite.setPosition(loc);
}

sf::Vector2f GameObj::getIntLocation() {
    return m_location;
}

