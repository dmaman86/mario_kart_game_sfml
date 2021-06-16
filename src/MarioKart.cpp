#include "MenuState.h"
#include "MarioKart.h"
#include "Macros.h"
#include "users_project.h"
#include "WelcomeState.h"

MarioKart::DataGame::DataGame(sf::RenderWindow& window)
	: window(&window), services(), user()
{

}

MarioKart::MarioKart()
	: m_window(sf::VideoMode(WITDH, HIGHT), "Mario Kart", sf::Style::Close),
	m_dataGame(new DataGame(m_window)) {
    m_window.setFramerateLimit(60);

    if (user_project == users::Liran)
    {
        m_dataGame->stateStack.AddState(StateStack::StateRef(new WelcomeState(m_dataGame)));
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
        {
		    if(m_dataGame->user.getId().size() > 1)
		        m_dataGame->services.deleteUser(&m_dataGame->user);
            m_window.close();
        }
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
