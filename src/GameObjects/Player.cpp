#include "Player.h"
#include "Pictures.h"
#include "Utilities.h"
#include "Sounds.h"

// const animation
const auto ANIMATION_TIME = 0.1f;

//========================== Constructor / Destructor =========================
Player::Player
	(const sf::Vector2f &loc, const sf::Vector2f& pos
		,const std::string& sprite, bool sound) :
	m_animation(Pictures::instance().getDriveAnimationData(sprite), m_sprite, ANIMATION_TIME,
		false, DRIVER_SIDE_LEN),
	PlayerBase::PlayerBase(Pictures::instance().getTexture(sprite), loc, pos),
	m_angle(0.0),m_force(0),m_acceleration(0),m_is_lock(0),m_last_pos(0, 0),
	m_cof(1),m_is_spin(false),m_is_smaller(false),m_smaller_time(0.f),
	m_soundOn(sound),m_last_pos_score(0),m_is_pressed(false),m_finish_line(false)
{
    m_sprite.setTexture(Pictures::instance().getTexture(Pictures::drivers));
	m_sprite.setOrigin(float(m_sprite.getTextureRect().width / 2),
		float(m_sprite.getTextureRect().height / 2));
	m_sprite.scale(STANDART_SCALE);
	m_backSound = sf::Sound(Sounds::instance().getSoundBuffer(Sounds::pipe));

	m_engine.openFromFile(Sounds::engine);
	m_engine.setLoop(true);
	m_engine.setVolume(0);
	m_engine.play();

	m_objClock.restart();
}
//=============================================================================
Player::Player(): m_animation(m_sprite),
	PlayerBase::PlayerBase(),
	m_angle(0.0),m_force(0),m_acceleration(0),m_is_lock(0),m_last_pos(0, 0),
	m_cof(1),m_is_spin(false),m_is_smaller(false),
	m_smaller_time(0.f),m_soundOn() ,m_last_pos_score(0),m_is_pressed(false),
	m_finish_line(false)
{
}

//============================ Public functions ===============================
void Player::Update(const float deltatime, const int fs)
{
	UpdateSpeed(deltatime);
	setLastScorePos(fs);
	UpdateLocation(deltatime);
	if (m_soundOn && m_force != 0)
		m_engine.setVolume(m_force * TWO_F);
}

//=============================================================================
void Player::UpdateBreaks()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->m_force -= BRAKES;
	}
}

//=============================================================================
void Player::CheckLap(const int fs)
{
	if (fs - getLastScorePos() >= m_finish_line && !m_is_lock)
		addLap();
	if (getLastScorePos() - fs  >= m_finish_line)
		decLap();
}

//=============================================================================
void Player::UpdateAnimation(const float time) 
{
	if (!m_is_spin)
		m_animation.update(time, m_is_pressed);
	else
		m_animation.spin();
}

//=============================================================================
void Player::DriveBack()
{
	if (!m_is_lock) {
		m_last_pos = m_location;
		if (m_soundOn)
			m_backSound.play();
	}
	m_is_lock = true;
}

//=============================================================================
void Player::SpinDriver() 
{
	m_force = 0;
	m_is_lock = true;
	m_is_spin = true;
	m_playerClock.restart();
}

//=============================================================================
void Player::DriveSmaller()
{
	if (!m_is_smaller)
	{
		m_is_smaller = true;
		m_smaller_time = m_objClock.getElapsedTime().asSeconds();
		this->m_sprite.setScale(m_sprite.getScale() / 2.f);
	}
}

//=============================================================================
void Player::setAngle(const float agl) {
	m_angle = agl;
	if (m_angle >= DEGREE_360) m_angle = 0;
	else if (m_angle < 0) m_angle += DEGREE_360;
}

//============================= protected functions ===========================
//=============================================================================
void Player::HandleLock(const float dt)
{
	if (calcLength(m_location, m_last_pos) >= TWO_F)
	{
		m_is_lock = false;
		m_force = 0.f;
	}
	else
	{
		m_location.x += 
			calcSinDegree(m_angle) * dt * - PlayerDefinitions::MAX_SPEED / ONE_AND_HALF;
		
		m_location.y -= 
			calcCosDegree(m_angle) * dt * - PlayerDefinitions::MAX_SPEED / ONE_AND_HALF;
	}
}
//=============================================================================
void Player::UpdateSpeed(const float delta) 
{
	UpdateSpecialSituations();
	if (!m_is_lock) {
		UpdateAcceleration();
		UpdateDirection(delta);
	}
	else if (!m_is_spin)
		HandleLock(delta);
}

//=============================================================================s
void Player::UpdateLocation(const float delta)
{
	if (!m_is_lock) {
		setMove();

		m_location.x +=
			calcSinDegree(m_angle) * delta * m_force / m_cof;

		m_location.y -=
			calcCosDegree(m_angle) * delta * m_force / m_cof;
	}
}

//=============================================================================
// Update the player by pressing the arrows
void Player::UpdateDirection(const float delta)
{
	auto s = m_force;
	// up 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		s += m_acceleration * delta;
		m_force = s;
	}
	else // down
	{
		s -= m_acceleration * delta;
		(s <= 0) ? m_force = 0 : m_force = s;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (this->getSpeed() > 0) {
			this->setAngle(this->getAngle() + THREE_F);
			if (!m_is_pressed) {
				m_is_pressed = true;
				m_playerClock.restart();
			}
		}
		if (m_sprite.getScale().x > 0)
			m_animation.setIndex(0);
		if (m_sprite.getScale().x >= 0)
			m_sprite.setScale(-1.f * m_sprite.getScale().x,
							  m_sprite.getScale().y);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (this->getSpeed() > 0) {
			this->setAngle(this->getAngle() - THREE_F);
			if (!m_is_pressed) {
				m_is_pressed = true;
				m_playerClock.restart();
			}
		}
		if (m_sprite.getScale().x < 0)
			m_animation.setIndex(0);
		m_sprite.setScale(abs(m_sprite.getScale().x), m_sprite.getScale().y);
	}
	else {
		this->m_is_pressed = false;
	}
}

//=============================================================================
void Player::UpdateAcceleration()
{
	auto speed_per = m_force / PlayerDefinitions::MAX_SPEED;
	if (speed_per < APPROXI_HALF)
		m_acceleration = PlayerDefinitions::EPSILON_SPEED / TWO_F;
	else if (speed_per < APPROXI_ONE)
		m_acceleration = PlayerDefinitions::EPSILON_SPEED * (ONE_F - speed_per);
	else
		m_acceleration = (APPROXI_ZERO * PlayerDefinitions::MAX_SPEED) / FOUR_F;
}

//=============================================================================
void Player::UpdateSpecialSituations()
{
	if (m_is_smaller && m_objClock.getElapsedTime().asSeconds() >
						m_smaller_time + THREE_F)
	{
		m_is_smaller = false;
		this->m_sprite.setScale(m_sprite.getScale() * TWO_F);
	}

	if (m_is_spin && m_playerClock.getElapsedTime().asSeconds() 
					 > ONE_AND_HALF) 
	{
		m_is_spin = false;
		m_is_lock = false;
	}
}
