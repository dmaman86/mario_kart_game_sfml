
#include "GameObj.h"

GameObj::GameObj(const sf::Texture &tex, const sf::Vector2f loc) {
    m_sprite.setTexture(tex);
    m_sprite.setPosition(loc);

}

GameObj::GameObj() {

}
