#include "User.h"
#include <iostream>

User::User():
        m_id(""),
        m_name(""),
        m_sprite(""),
        m_music(false),
        m_sound(true),
        m_host(false),
        m_inGame(false),
        m_map_game(""),
        m_idOther(""),
		m_online(false),
		m_numberCoins(0),
		m_drivers(),
		m_max_drivers(0)
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

const std::string& User::getName()
{
    return m_name;
}

const std::string& User::getOtherId()
{
    return m_idOther;
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

const std::string& User::getSprite()
{
    return m_sprite;
}

void User::updateInGame(bool game)
{
    m_inGame = game;
}

bool User::getInGame()
{
    return m_inGame;
}

bool User::getIfSound()
{
    return m_sound;
}

void User::setIfSound(bool sound)
{
    m_sound = sound;
}

void User::setHost(bool host)
{
    m_host = host;
}

bool User::getIfHost()
{
    return m_host;
}

void User::setMapGame(const std::string& map)
{
    m_map_game = map;
}

const std::string& User::getMapGame()
{
    return m_map_game;
}

bool User::getIfMusic()
{
    return m_music;
}

void User::initDrivers()
{
    m_drivers.emplace_back("mario.png");
    m_drivers.emplace_back("peach.png");
    m_max_drivers = 2;
}

void User::setIfMusic(bool music)
{
    m_music = music;
}

void User::setOnline(const bool b)
{
    m_online = b;
}

const bool User::getOnline()
{
    return m_online;
}

const int User::getCoins()const
{
    return m_numberCoins;
}

void User::setCoins(int coins)
{
    m_numberCoins = coins;
}

const std::string& User::getDrive(size_t i)
{
    return m_drivers[i];
}

const int User::getMaxDrivers()
{
    return m_max_drivers;
}

void User::setDrive(const std::string& drive_name)
{
    std::vector<std::string>::iterator it;
    it = std::find(m_drivers.begin(), m_drivers.end(), drive_name);
    if(it == m_drivers.end())
    {
         m_drivers.emplace_back(drive_name);
         m_max_drivers++;
    }
}