#include "Pictures.h"
#include "TraficLight.h"
const auto AnimationTime = 0.5;
const auto TRAFTTLIGHTSCALE = 10;


TraficLight::TraficLight():m_animation(Pictures::instance().getTraffic(),m_sprite,AnimationTime){
    m_sprite.setTexture(Pictures::instance().getTexture(Pictures::GameStartGui));
    m_sprite.setPosition(150,150);
    m_sprite.scale(TRAFTTLIGHTSCALE,TRAFTTLIGHTSCALE);


}

void TraficLight::draw(sf::RenderWindow & win) {
        win.draw(m_sprite);
}

void TraficLight::updateAnimation(sf::Time time) {

   m_animation.update(time,true);

}
