#include "UserNetwork.h"

UserNetwork::UserNetwork( std::string id, std::string name, std::string level, std::string sprite):
        m_id( id ), m_name( name ), m_sprite( sprite ),
                m_level( level )
{

}

void UserNetwork::setId(std::string & id)
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

void UserNetwork::updatePosition(float x, float y)
{
    m_positionX = x;
    m_positionY = y;
}

void UserNetwork::setSprite( std::string& sprite )
{
    m_sprite = sprite;
}