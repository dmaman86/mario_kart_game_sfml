#include "Pictures.h"
#include "StartCloud.h"
const auto ANIMATION_TIME = 0.1;
const auto CLOUDSCALE = 3;
const auto XPOSITION = 650;
const auto YPOSITION = 120;

void StartCloud::draw(sf::RenderWindow & win){
    win.draw(m_sprite);

}

StartCloud::StartCloud(): m_animation(Pictures::instance().getCloud(),m_sprite,ANIMATION_TIME,true,Pictures::instance().getCloud().size()) {
    m_sprite.setTexture(Pictures::instance().getTexture(Pictures::GameStartGui));
    m_sprite.setPosition(XPOSITION,YPOSITION);
    m_sprite.scale(CLOUDSCALE,CLOUDSCALE);

}

void StartCloud::UpdateAnimation(const float time) {
    m_animation.update(time,true);

}
