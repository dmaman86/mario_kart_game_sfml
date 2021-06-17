#include "Pictures.h"
#include "TraficLight.h"
const auto AnimationTime = 400000.f;

TraficLight::TraficLight():m_animation(Pictures::instance().getTraffic(),m_sprite,AnimationTime){
    m_sprite.setTexture(Pictures::instance().getTexture(Pictures::GameStartGui));
    m_sprite.setPosition(150,150);
    m_sprite.scale(10,10);


}

void TraficLight::draw(sf::RenderWindow & win) {
        win.draw(m_sprite);
}

void TraficLight::updateAnimation(sf::Time time) {

   m_animation.update(time,true);

}
