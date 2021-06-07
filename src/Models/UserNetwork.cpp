#include "UserNetwork.h"
#include <iostream>

UserNetwork::UserNetwork( std::string id, std::string name, std::string sprite ):
        m_id( id ),
        m_name( name ),
        m_sprite( sprite ),
        m_angle(0),
        m_speed(0),
        m_position()
{

}

void UserNetwork::setId(std::string id)
{
    m_id = id;
}

const std::string& UserNetwork::getId()
{
    return m_id;
}

void UserNetwork::setName( std::string& name )
{
    m_name = name;
}

void UserNetwork::updatePosition()
{

}

void UserNetwork::setSprite( std::string& sprite )
{
    m_sprite = sprite;
}