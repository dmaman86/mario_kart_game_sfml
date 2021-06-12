#include "UserNetwork.h"
#include <iostream>

UserNetwork::UserNetwork():
        m_id(""),
        m_name(""),
        m_sprite(""),
        m_sound(false),
        m_host(false),
        m_inGame(false),
        m_map_game(""),
        m_idOther(""),
		m_online(false),
		m_music(false)
{

}

UserNetwork::UserNetwork( std::string id, std::string name, std::string sprite, std::string map ):
        m_id( id ),
        m_name( name ),
        m_sprite( sprite ),
        m_map_game(map),
		m_online(false)
{

}

void UserNetwork::setId(std::string id)
{
    m_id = id;
}

void UserNetwork::setIdOther(std::string other)
{
    m_idOther = other;
}

const std::string& UserNetwork::getId()
{
    return m_id;
}

void UserNetwork::setName( std::string name )
{
    m_name = name;
}

void UserNetwork::setSprite( std::string sprite )
{
    m_sprite = sprite;
}