#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

/* Abstract class State */
class State
{
public:
    virtual void Init() = 0;
    virtual void HandleEvent( const sf::Event& ) = 0;
    virtual void Update( float ) = 0;
    virtual void Draw() = 0;

    virtual void Pause(){ }
    virtual void Resume(){ }
}; // end class