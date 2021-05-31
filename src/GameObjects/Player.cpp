#include "Macros.h"
#include "Player.h"
#include "Pictures.h"
Player::Player(const sf::Vector2f & loc, const sf::Vector2f &pos)
        : GameObj::GameObj(Pictures::instance().getTexture(Pictures::MarioDriver), loc), m_location(pos),m_angle(0.0),m_speed(0) {

    m_sprite.setTextureRect(sf::Rect(0,0,33,33));
    m_sprite.scale(3,3);
}

Player::Player() {

}

sf::Vector2f Player::getIntLocation() {
    return m_location;
}

void Player::setIntLocation(const sf::Vector2f &loc) {
        m_location = loc;
}

void Player::setIntLocation(float delta,int floor) {

    if(!floor) {
        m_location.x += std::sin(m_angle * 3.141592 / 180) * delta * m_speed;
        m_location.y -= std::cos(m_angle * 3.141592 / 180) * delta * m_speed;
    }
    else if(floor == 1)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            m_location.x -= std::sin(m_angle * 3.141592 / 180) * delta * m_speed;
            m_location.y += std::cos(m_angle * 3.141592 / 180) * delta * m_speed;
        }
    }
    else if (floor == 2)
    {
        m_location.x += std::sin(m_angle * 3.141592 / 180) * delta * (m_speed/2);
        m_location.y -= std::cos(m_angle * 3.141592 / 180) * delta * (m_speed/2);
    }

}
void Player::updateDir()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->speedUp();
    else
        this->speedDown();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        if(this->getSpeed() > 0)
            this->setAngle(this->getAngle()+2);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if(this->getSpeed() > 0)
            this->setAngle(this->getAngle()-2);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        this->m_speed-=0.25;
    }
}

void Player::setAngle(float agl) {
    m_angle = agl;
    if (m_angle >= 360) m_angle = 0;


}

float Player::getAngle() {
    return m_angle;

}

void Player::speedUp() {
    if(m_speed < CAR_SPEED)

        if(m_speed == 0)m_speed =1;
        else
        m_speed += sqrt(sqrt(sqrt(std::abs(m_speed))));

}

void Player::speedDown() {

    if(m_speed > 0)
         m_speed -= 0.25;

}

float Player::getSpeed() const {
    return m_speed;
}
