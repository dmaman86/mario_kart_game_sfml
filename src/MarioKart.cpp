#include "MenuState.h"
#include "MarioKart.h"
#include "RaceState.h"
#include "Macros.h"
#include "user.h"
#include "WelcomeState.h"

MarioKart::DataGame::DataGame(sf::RenderWindow& window)
	: window(&window), http(HttpNetwork::url), user()
{

}

MarioKart::MarioKart()
	: m_window(sf::VideoMode(WITDH, HIGHT), "Mario Kart", sf::Style::Close),
	m_dataGame(new DataGame(m_window)) {
    m_window.setFramerateLimit(60);

    if (User == users::Liran)
    {
        m_dataGame->stateStack.AddState(StateStack::StateRef(new WelcomeState(m_dataGame)));
    }
    if (User == users::Liron)
    {
	    m_dataGame->stateStack.AddState(StateStack::StateRef(new RaceState(m_dataGame)));
    }    
	if (User == users::Daniel)
	{
		m_dataGame->stateStack.AddState(StateStack::StateRef(new RaceState(m_dataGame)));
	}
}

void MarioKart::run()
{
	float newTime, frameTime;

	float currentTime = m_clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (m_window.isOpen())
	{
		m_dataGame->stateStack.ProcessStateChanges();

		auto dt = m_clock.getElapsedTime().asSeconds();
		m_clock.restart();
		/*  newTime = m_clock.getElapsedTime().asSeconds();
		  frameTime = newTime - currentTime;

		  if (frameTime > 0.25f)
			  frameTime = 0.25f;

		  currentTime = newTime;
		  accumulator += frameTime;

		  while (accumulator >= m_dt)
		  {*/
		processInput();
		update(dt);
		//    accumulator -= m_dt;
	   // }
		render();
	}
}

void MarioKart::processInput()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
	    m_dataGame->stateStack.GetActiveState()->HandleEvent(event);

		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}

void MarioKart::update(double dt)
{
	m_dataGame->stateStack.GetActiveState()->Update(dt);
}

void MarioKart::render()
{
	m_window.clear();

	m_dataGame->stateStack.GetActiveState()->Draw();

	m_window.setView(m_window.getDefaultView());

	m_window.display();
}
