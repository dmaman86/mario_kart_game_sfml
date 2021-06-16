#include "User.h"
#include <iostream>

User::User():
        m_id(""),
        m_name(""),
        m_sprite(""),
        m_sound(false),
        m_host(false),
        m_inGame(false),
        m_map_game(""),
        m_idOther(""),
		m_online(false),
		m_numberCoins(0),
		m_drivers()
{
    initDrivers();
}

User::User(std::string id, std::string name, std::string sprite, std::string map ):
        m_id( id ),
        m_name( name ),
        m_sprite( sprite ),
        m_map_game(map),
		m_online(false)
{

}

void User::setId(std::string id)
{
    m_id = id;
}

void User::setIdOther(std::string other)
{
    m_idOther = other;
}

const std::string& User::getId()
{
    return m_id;
}

void User::setSprite(std::string sprite )
{
    m_sprite = sprite;
}

void User::setName(std::string name)
{
    m_name = name;
}

void User::initDrivers()
{
    m_drivers.emplace_back("mario.png");
    m_drivers.emplace_back("peach.png");
}