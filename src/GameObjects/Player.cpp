#include "Macros.h"
#include "Player.h"
#include "Pictures.h"
#include<iostream>
#include "Utilities.h"

Player::Player(const sf::Vector2f loc, const sf::Vector2f pos, std::string id, std::string sprite):
    m_animation(Pictures::instance().m_drivers[3],Direction::Left,m_sprite),
    PlayerBase::PlayerBase(Pictures::instance().getTexture(sprite), loc, pos),
	m_angle(0.0),
	m_speed(0),
	m_force(0),
	m_mass(20),
	m_acceleration(0),
	m_is_lock(0),
	m_last_pos(0,0),
	m_coefficient_of_friction(1),
    m_idHost( id )
{
	m_sprite.setTextureRect(sf::Rect(0, 0, 33, 33));
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
	m_sprite.scale(3, 3);
}

Player::Player(): m_animation (Pictures::instance().m_drivers[0],Direction::Left,m_sprite) {

}


void Player::setIntLocation(const sf::Vector2f& loc) {
	m_location = loc;
}

void Player::updateAcceleration()
{
	m_force = m_mass * (m_acceleration + 0.01);
	m_acceleration = m_force / m_mass;
}

void Player::speedUp(float delta) {
	std::cout << m_force << " " << m_mass << " " << m_acceleration << '\n';
	if (m_force < MAX_SPEED)
		if (m_force <= 0) {
			m_force = 0.05;
			//m_acceleration = 0.05;
		}
		else
			updateAcceleration();
}

void Player::speedDown(float delta) {

	if (m_force > 0) {
		(m_force <= 0.05) ? m_force = 0 :
			m_force -= sqrt(sqrt(sqrt(std::abs(m_force))));
	}
}

void Player::updateSpeed(float delta) {

  //  m_animation.update(delta);
	if (m_is_lock) {
		handleLock(delta);
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		float s = m_force;
		float speed_per = s / MAX_SPEED;
		if (speed_per < 0.45)
			m_acceleration = EPSILON_SPEED / 2.0;
		else if (speed_per < 0.95)
			m_acceleration = EPSILON_SPEED * (1.0 - speed_per);
		else
			m_acceleration = (0.05 * MAX_SPEED) / 4.0;
		s += m_acceleration * delta;
		m_force = s;
	}
	else
	{
		float s = m_force;
		float speed_per = s / MAX_SPEED;
		if (speed_per < 0.45)
			m_acceleration = EPSILON_SPEED / 2.0;
		else if (speed_per < 0.95)
			m_acceleration = EPSILON_SPEED * (1.0 - speed_per);
		else
			m_acceleration = (0.05 * MAX_SPEED) / 4.0;
		s -= m_acceleration * delta;
		
		if(s <=0 )
			m_force = 0;
		else
			m_force = s;
	}
}
void Player::updateDir()
{
	if (m_is_lock) {
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		if (this->getSpeed() > 0)
			this->setAngle(this->getAngle() + 3);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (this->getSpeed() > 0)
			this->setAngle(this->getAngle() - 3);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->m_force -= 0.25;
	}
}

void Player::updateLocation(float delta)
{
	if (!m_is_lock) {
		m_location.x += std::sin(m_angle * 3.141592 / 180) * delta * m_force / m_coefficient_of_friction;
		m_location.y -= std::cos(m_angle * 3.141592 / 180) * delta * m_force / m_coefficient_of_friction;
	}
}

void Player::setCoefficientOfFriction(const float cof)
{
	m_coefficient_of_friction = cof;
}

void Player::setAngle(float agl) {
	m_angle = agl;
	if (m_angle >= 360) m_angle = 0;
	else if (m_angle < 0) m_angle += 360;
}

float Player::getAngle() {
	return m_angle;
}

float Player::getSpeed() const {
	return m_force;
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
		m_location.x += std::sin(m_angle * 3.141592 / 180) * dt * -m_force / 1.5;
		m_location.y -= std::cos(m_angle * 3.141592 / 180) * dt * -m_force / 1.5;
	}
}

void Player::driveBack()
{
	if (!m_is_lock) {
		m_last_pos = m_location;
	}
	m_is_lock = true;
}
