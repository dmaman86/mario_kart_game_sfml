#include "Macros.h"
#include "Player.h"
#include "Pictures.h"
#include<iostream>

Player::Player(const sf::Vector2f loc, const sf::Vector2f pos)
	: GameObj::GameObj(Pictures::instance().getTexture(Pictures::MarioDriver), loc, pos), 
	m_angle(0.0), m_speed(0), m_force(0), m_mass(20), m_acceleration(0){

	m_sprite.setTextureRect(sf::Rect(0, 0, 33, 33));
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
	m_sprite.scale(3, 3);
}

Player::Player() {

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
		//m_speed -= sqrt(sqrt(sqrt(std::abs(m_speed))));
		(m_force <= 0.05) ? m_force = 0 :
			m_force -= sqrt(sqrt(sqrt(std::abs(m_force))));
	}
}

void Player::setIntLocation(float delta, int floor) {
	



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
		//this->speedUp(delta);
	}
	//else
	//	this->speedDown(delta);


	//std::cout << m_force << '\n';

	if (!floor) {
		m_location.x += std::sin(m_angle * 3.141592 / 180) * delta * m_force;
		m_location.y -= std::cos(m_angle * 3.141592 / 180) * delta * m_force;
	}
	else if (floor == 1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			m_location.x -= std::sin(m_angle * 3.141592 / 180) * delta * m_force;
			m_location.y += std::cos(m_angle * 3.141592 / 180) * delta * m_force;
		}
	}
	else if (floor == 2)
	{
		m_location.x += std::sin(m_angle * 3.141592 / 180)  * (m_force / 2);
		m_location.y -= std::cos(m_angle * 3.141592 / 180)  * (m_force / 2);
	}

}
void Player::updateDir()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		if (this->getSpeed() > 0)
			this->setAngle(this->getAngle() + 2);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (this->getSpeed() > 0)
			this->setAngle(this->getAngle() - 2);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->m_force -= 0.25;
	}
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
