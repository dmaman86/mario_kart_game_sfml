#include "TestState.h"

TestState::TestState(MarioKart::GameDataRef data)
    : m_data( data )
{

}

void TestState::Init()
{
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    if(socket.connect(ip.toString(), 2525) != sf::Socket::Done)
    {
        logl("Could not connect to the server\n");
    }
    else
    {
        isConnected = true;
        logl("Connected to the server\n");
    }
}

void TestState::HandleEvent(const sf::Event & event)
{
    if (sf::Event::Closed == event.type)
    {
        m_data->window->close();
    }
}

void TestState::Update(float dt)
{
    std::thread reception_thred(&TestState::ReceivePackets, this, &socket);

    while(true)
    {
        if(isConnected)
        {
            std::string user_input;
            std::getline(std::cin, user_input);

            sf::Packet reply_packet;
            reply_packet << user_input;

            SendPacket(reply_packet);
        }
    }
    socket.disconnect();
}

void TestState::Draw()
{
    sf::RenderWindow& window = *m_data->window;
}

void TestState::ReceivePackets(sf::TcpSocket * socket)
{
    while(true)
    {
        if(socket->receive(last_packet) == sf::Socket::Done)
        {
            std::string received_string;
            std::string sender_address;
            unsigned short sender_port;
            last_packet >> received_string >> sender_address >> sender_port;
            logl("From (" << sender_address << ":" << sender_port << "): " << received_string);
        }

        std::this_thread::sleep_for((std::chrono::milliseconds)100);
    }
}

void TestState::SendPacket(sf::Packet & packet)
{
    if(packet.getDataSize() > 0 && socket.send(packet) != sf::Socket::Done)
    {
        logl("Could not send packet");
    }
}
