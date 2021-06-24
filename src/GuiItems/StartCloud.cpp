#include "Pictures.h"
#include "StartCloud.h"

const auto ANIMATION_TIME = 0.1f;
const auto CLOUDSCALE = 3.f;
const auto XPOSITION = 650.f;
const auto YPOSITION = 120.f;

StartCloud::StartCloud(): m_animation(Pictures::instance().getCloud(),
	                                    m_sprite,
	                                    ANIMATION_TIME,
	                                    true,
                                        (unsigned int)(Pictures::instance().getCloud().size()))
{
    m_sprite.setTexture(Pictures::instance().getTexture(Pictures::GameStartGui));
    m_sprite.setPosition(XPOSITION,YPOSITION);
    m_sprite.scale(CLOUDSCALE,CLOUDSCALE);

}

void StartCloud::UpdateAnimation(const float time)
{
    m_animation.update(time,true);
}

void StartCloud::draw(sf::RenderWindow & win)
{
    win.draw(m_sprite);
}
