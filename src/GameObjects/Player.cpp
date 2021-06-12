#include "Macros.h"
#include "Player.h"
#include "Pictures.h"
#include<iostream>
#include "Utilities.h"

Player::Player(const sf::Vector2f loc, const sf::Vector2f pos,std::string sprite) :
        m_animation(Pictures::instance().getDriveAnimationData(sprite),Direction::Left,m_sprite),
        PlayerBase::PlayerBase(Pictures::instance().getTexture(sprite), loc, pos),
        m_angle(0.0),
        m_force(0),
        m_acceleration(0),
        m_is_lock(0),
        m_last_pos(0,0),
        m_coefficient_of_friction(1),
        m_is_spin(false),
        m_lap(0)
{
	m_sprite.setTextureRect(sf::Rect(0, 0, 33, 33));
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
	m_sprite.scale(3, 3);
}

Player::Player(): m_animation (Pictures::instance().m_drivers[0],Direction::Left,m_sprite) {

}

void Player::updateSpeed(float delta) {

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		s += m_acceleration * delta;
		m_force = s;
	}
	else
	{
		s -= m_acceleration * delta;
		(s <=0 )?m_force = 0:m_force = s;

	}

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if (this->getSpeed() > 0){
                    this->setAngle(this->getAngle() + 3);
                    if(!m_is_pressed) {
                        m_is_pressed = true;
                        m_playerClock.restart();
                    }
                }
                m_sprite.setScale(-3,3);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                if (this->getSpeed() > 0){
            this->setAngle(this->getAngle() - 3);
            if(!m_is_pressed) {
                m_is_pressed = true;
                m_playerClock.restart();
            }
        }
        m_sprite.setScale(3,3);
    }
    else {
        this->m_is_pressed = false;

    }
}
void Player::updateDir()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->m_force -= 0.25;
	}
}

void Player::updateLocation(float delta)
{
	if (!m_is_lock) {
		m_location.x += calcSinDegree(m_angle) * delta * m_force / m_coefficient_of_friction;
		m_location.y -= calcCosDegree(m_angle)* delta * m_force / m_coefficient_of_friction;
	}
}

void Player::setCoefficientOfFriction(const float cof)
{
	m_coefficient_of_friction = cof;
}



float Player::getAngle() {
	return m_angle;
}

float Player::getSpeed() const {
	return m_force;
}

void Player::setAngle(float agl) {
    m_angle = agl;
    if (m_angle >= 360) m_angle = 0;
    else if (m_angle < 0) m_angle += 360;
}

void Player::handleLock(float dt)
{
	if (calcLength(m_location, m_last_pos) >= 4.5)
	{
		m_is_lock = false;
		m_force = 0;
	}
	else
	{
		m_location.x += calcSinDegree(m_angle) * dt * -m_force / 1.5;
		m_location.y -= calcCosDegree(m_angle) * dt * -m_force / 1.5;
	}
}

void Player::driveBack()
{
	if (!m_is_lock) {
		m_last_pos = m_location;
	}
	m_is_lock = true;
}

void Player::spindriver() {
    m_force = 0;
    m_is_lock = true;
    m_is_spin = true;
   m_playerClock.restart();

}

void Player::updateAnimation() {

    if(!m_is_spin)
        m_animation.update(m_playerClock.getElapsedTime(), m_is_pressed);
    else
        m_animation.spin(m_playerClock.getElapsedTime().asSeconds());

}

void Player::setLastScorePos(unsigned int score) {m_last_pos_score = score;}

int Player::getLastScorePos() const {return m_last_pos_score;}

