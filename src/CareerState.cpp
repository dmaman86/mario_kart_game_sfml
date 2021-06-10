#include"CareerState.h"
#include "Pictures.h"
#include "MenuState.h"
#include "GetDataState.h"

CareerState::CareerState(MarioKart::GameDataRef& data): m_data(data),
                                                    m_backMenu(false),
                                                    m_background()
{
}

void CareerState::Init()
{
    sf::Vector2u textureSize, windowSize;
    windowSize = m_data->window->getSize();
    textureSize = Pictures::instance().getTexture(Pictures::menuBackground).getSize();

    m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
    m_background.setScale((float)windowSize.x / textureSize.x,
                          (float)windowSize.y / textureSize.y);

    m_back.setTexture(Pictures::instance().getTexture(Pictures::back));
	m_new_game.setTexture(Pictures::instance().getTexture(Pictures::new_game));
	m_load_game.setTexture(Pictures::instance().getTexture(Pictures::load_game));
    m_click.setBuffer(Sounds::instance().getSoundBuffer(Sounds::click));

	m_new_game.setPosition((float)windowSize.x / 2.5,(float)windowSize.y / 2.5);
	m_load_game.setPosition((float)windowSize.x / 2.5, (float)windowSize.y / 2.5 + 100);

}

void CareerState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type) {
        m_click.play();
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseButton.x, event.mouseButton.y });
        if (m_back.getGlobalBounds().contains(location)) {
            m_backMenu = true;
        }
		if (m_new_game.getGlobalBounds().contains(location)) {

			m_data->stateStack.AddState(StateStack::StateRef(new GetDataState(m_data)));
		}
		if (m_load_game.getGlobalBounds().contains(location)) {
		}

    }
}

void CareerState::Update(float)
{
    setVolume();
    if (m_backMenu)
    {
        m_data->stateStack.RemoveState();
    }
}

void CareerState::Draw()
{
	m_data->window->draw(m_background);
	m_data->window->draw(m_back);
	m_data->window->draw(m_new_game);
	m_data->window->draw(m_load_game);
}

void CareerState::setVolume()
{
    if(m_data->user.getIfSound())
        m_click.setVolume(100);
    else
        m_click.setVolume(0);
}

