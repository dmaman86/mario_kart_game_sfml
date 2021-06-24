#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "StateStack.h"
#include "User.h"
#include "Services.h"


namespace sf
{
    class RenderWindow;
}

class MarioKart
{
public:
    struct DataGame
    {
        DataGame( sf::RenderWindow& );

        sf::RenderWindow* window;
        StateStack stateStack;
        Services services;
        User user;
        sf::Music menuMusic;
    };
    typedef std::shared_ptr<DataGame> GameDataRef;

public:
    // constructor & destructor
    MarioKart();
    ~MarioKart() = default;
    // public function
    void run();

private:
    // private members
    const float m_dt = 1.0f / 60.0f;
    sf::Clock m_clock;
    sf::RenderWindow m_window;
    GameDataRef m_dataGame;

    // private functions
    void processInput();
    void update(const float);
    void render();
};