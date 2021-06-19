#include "Pictures.h"
#include "StartCloud.h"
const auto AnimationTime = 0.1;
const auto CLOUDSCALE = 3;

void StartCloud::draw(sf::RenderWindow & win){
    win.draw(m_sprite);

}

StartCloud::StartCloud(): m_animation(Pictures::instance().getCloud(),m_sprite,AnimationTime,true,Pictures::instance().getCloud().size()) {
    m_sprite.setTexture(Pictures::instance().getTexture(Pictures::GameStartGui));
    m_sprite.setPosition(600,200);
    m_sprite.scale(CLOUDSCALE,CLOUDSCALE);

}

void StartCloud::updateAnimation(float time) {
    m_animation.update(time,true);

}
