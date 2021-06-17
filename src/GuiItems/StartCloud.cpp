#include "Pictures.h"
#include "StartCloud.h"
const auto AnimationTime =0.1f;

void StartCloud::draw(sf::RenderWindow & win){
    win.draw(m_sprite);

}

StartCloud::StartCloud(): m_animation(Pictures::instance().getCloud(),m_sprite,AnimationTime) {
    m_sprite.setTexture(Pictures::instance().getTexture(Pictures::GameStartGui));
    m_sprite.setPosition(600,200);
    m_sprite.scale(5,5);

}

void StartCloud::updateAnimation(sf::Time time) {
    m_animation.update(time,true);

}
