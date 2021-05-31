#include "MarioKart.h"
#include "RaceState.h"
#include "TestState.h"
#include "Macros.h"

MarioKart::DataGame::DataGame(sf::RenderWindow & window)
    : window(&window)
{

}

MarioKart::MarioKart()
    : m_window(sf::VideoMode( WITDH, HIGHT ), "Mario Kart"),
      m_dataGame( new DataGame( m_window ) )
{
    m_window.setFramerateLimit(60);
    //m_dataGame->stateStack.AddState( StateStack::StateRef( new TestState(m_dataGame)));
    m_dataGame->stateStack.AddState( StateStack::StateRef( new RaceState(m_dataGame)), true);
}

void MarioKart::run()
{
    float newTime, frameTime;


    float currentTime = m_clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    while (m_window.isOpen())
    {
        m_dataGame->stateStack.ProcessStateChanges();

        newTime = m_clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;

        if (frameTime > 0.25f)
            frameTime = 0.25f;

        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= m_dt)
        {
            processInput();
            update( m_dt );
            accumulator -= m_dt;
        }
        render();
    }
}

void MarioKart::processInput()
{
    sf::Event event;
    while( m_window.pollEvent( event ) )
    {
        try{
              m_dataGame->stateStack.GetActiveState()->HandleEvent( event );
            }

        catch (std::exception& e)
        {
            std::cout<<e.what();
        }

        if( event.type == sf::Event::Closed )
            m_window.close();
    }
}

void MarioKart::update( double dt )
{
    m_dataGame->stateStack.GetActiveState()->Update( dt );
}

void MarioKart::render()
{
    m_window.clear();

    m_dataGame->stateStack.GetActiveState()->Draw();

    m_window.setView( m_window.getDefaultView() );

    m_window.display();
}
