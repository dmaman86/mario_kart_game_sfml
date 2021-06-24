#include "MenuState.h"
#include "MarioKart.h"
#include "Macros.h"
#include "WelcomeState.h"
#include "Pictures.h"

//=======================================================================
// init struct
MarioKart::DataGame::DataGame(sf::RenderWindow& window)
	: window(&window), services(), user()
{
	menuMusic.openFromFile(Sounds::menu);
	menuMusic.setLoop(true);
}

//======================== Constructor =============================
MarioKart::MarioKart()
	: m_window(sf::VideoMode(DimensionWindow::WIDTH, DimensionWindow::HEIGHT),
               "Mario Kart",
               sf::Style::Close+sf::Style::Resize),
	  m_dataGame(new DataGame(m_window))
{
    m_window.setFramerateLimit(60);

    m_dataGame->stateStack.AddState(StateStack::StateRef(new
                                        WelcomeState(m_dataGame)));
}

//=======================================================================
void MarioKart::run()
{
	while (m_window.isOpen())
	{
		m_dataGame->stateStack.ProcessStateChanges();
		auto dt = m_clock.getElapsedTime().asSeconds();
		m_clock.restart();
		processInput();
		update(dt);
		render();
	}
}

//=======================================================================
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

//=======================================================================
void MarioKart::update(double dt)
{
	m_dataGame->stateStack.GetActiveState()->Update(dt);
}

//=======================================================================
void MarioKart::render()
{
	m_window.clear();

	m_dataGame->stateStack.GetActiveState()->Draw();

	m_window.setView(m_window.getDefaultView());
	m_window.display();
}
