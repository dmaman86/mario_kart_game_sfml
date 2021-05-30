#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include "State.h"
#include "MarioKart.h"

#include <thread>
#include <chrono>
#include <SFML/Network.hpp>

#define logl(x) std::cout << x << std::endl
#define log(x) std::cout << x


/* Test state to test server */
class TestState : public State
{
public:
    TestState( MarioKart::GameDataRef );
    ~TestState() = default;

    void Init() override;
    void HandleEvent( const sf::Event& ) override;
    void Update( float ) override;
    void Draw() override;

    void Connect(const char *, unsigned short);
    void ReceivePackets(sf::TcpSocket *);
    void SendPacket(sf::Packet &);

private:
    MarioKart::GameDataRef m_data;
    sf::TcpSocket socket;
    sf::Packet last_packet;

    bool isConnected = false;
};
