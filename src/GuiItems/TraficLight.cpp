#include "Pictures.h"
#include "TraficLight.h"
#include "Sounds.h"
const auto AnimationTime = 1.f;
const auto TRAFTTLIGHTSCALE = 7.f;


TraficLight::TraficLight():m_animation(Pictures::instance().getTraffic(),m_sprite,AnimationTime,false,Pictures::instance().getTraffic().size()){
    m_sprite.setTexture(Pictures::instance().getTexture(Pictures::GameStartGui));
    m_sprite.setPosition(150,150);
    m_sprite.scale(TRAFTTLIGHTSCALE,TRAFTTLIGHTSCALE);
    m_sound = sf::Sound(Sounds::instance().getSoundBuffer(Sounds::startGame));


}

void TraficLight::draw(sf::RenderWindow & win) {
        win.draw(m_sprite);
}

void TraficLight::updateAnimation(float time) {

   m_animation.update(time,true);

}
