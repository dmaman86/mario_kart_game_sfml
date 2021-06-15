
#include "SeconedPlayer.h"
#include "Macros.h"
void SeconedPlayer::updateSpeed(const float delta) {


    if (m_is_smaller&& m_playerClock.getElapsedTime().asSeconds() > m_smaller_time + 4.f)
    {
        m_is_smaller = false;
        this->m_sprite.setScale(m_sprite.getScale() * 2.f);
    }

    if(m_is_spin && m_playerClock.getElapsedTime().asSeconds() > 1.5f) {
        m_is_spin = false;
        m_is_lock = false;
    }

    if (m_is_lock) {
        if(m_is_spin)return;
        handleLock(delta);
        return;
    }

    float s = m_force;
    float speed_per = s / MAX_SPEED;
    if (speed_per < 0.45)
        m_acceleration = EPSILON_SPEED / 2.0;
    else if (speed_per < 0.95)
        m_acceleration = EPSILON_SPEED * (1.0 - speed_per);
    else
        m_acceleration = (0.05 * MAX_SPEED) / 4.0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        s += m_acceleration * delta;
        m_force = s;
    }
    else
    {
        s -= m_acceleration * delta;
        (s <=0 )?m_force = 0:m_force = s;

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (this->getSpeed() > 0){
            this->setAngle(this->getAngle() + 3);
            if(!m_is_pressed) {
                m_is_pressed = true;
                m_playerClock.restart();
            }
        }
        if(m_sprite.getScale().x > 0 )
            m_animation.setIndex(0);
        if(m_sprite.getScale().x >= 0)
            m_sprite.setScale(-1*m_sprite.getScale().x, m_sprite.getScale().y);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (this->getSpeed() > 0){
            this->setAngle(this->getAngle() - 3);
            if(!m_is_pressed) {
                m_is_pressed = true;
                m_playerClock.restart();
            }
        }
        if(m_sprite.getScale().x < 0 )
            m_animation.setIndex(0);
        m_sprite.setScale(abs(m_sprite.getScale().x), m_sprite.getScale().y);
    }
    else {
        this->m_is_pressed = false;

    }

}

SeconedPlayer::SeconedPlayer(const sf::Vector2f loc, const sf::Vector2f pos,std::string sprite) : Player(loc, pos, sprite) {
    m_sprite.setTextureRect(sf::Rect(0, 0, 33, 33));
    m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
    m_sprite.scale(3, 3);
}
