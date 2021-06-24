#include "Pictures.h"
#include "TraficLight.h"
#include "Sounds.h"
const auto ANIMATION_TIME = 1.f;
const auto TRAFTTLIGHTSCALE = 7.f;
const auto XPOSITION = 100.f;
const auto YPOSITION = 100.f;

TraficLight::TraficLight():m_animation(Pictures::instance().getTraffic(),
	                                    m_sprite,
	                                    ANIMATION_TIME,
	                                    false,
                                        (unsigned int)(Pictures::instance().getTraffic().size()))
{
    m_sprite.setTexture(Pictures::instance().getTexture(Pictures::GameStartGui));
    m_sprite.setPosition(XPOSITION,YPOSITION);
    m_sprite.scale(TRAFTTLIGHTSCALE,TRAFTTLIGHTSCALE);
    m_sound = sf::Sound(Sounds::instance().getSoundBuffer(Sounds::startGame));
}

void TraficLight::draw(sf::RenderWindow & win)
{
    win.draw(m_sprite);
}

void TraficLight::UpdateAnimation(const float time)
{
    m_animation.update(time,true);
}
