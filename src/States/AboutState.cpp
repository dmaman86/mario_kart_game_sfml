#include "AboutState.h"
#include "Pictures.h"
#include "MenuState.h"

AboutState::AboutState(MarioKart::GameDataRef& data):
        m_data(data),
        StateOfMenu(data),
        m_about()
{

}

void AboutState::Init()
{
    sf::Vector2u windowSize(m_data->window->getSize());
    auto sprite = sf::Sprite();
    sprite.setTexture(Pictures::instance().getTexture(Pictures::about_picture));
    m_about.setTexture(sprite.getTexture());
    m_about.setOrigin(sprite.getGlobalBounds().width / 2,
                      sprite.getGlobalBounds().height / 2);
    m_about.setPosition(windowSize.x /2, windowSize.y /2 );
    m_about.setSize(sf::Vector2f(400, 400));
    m_about.setOutlineThickness(5.f);
}

void AboutState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type) {
        m_click.play();
        auto location = m_data->window->mapPixelToCoords(
                { event.mouseButton.x, event.mouseButton.y });
        if (m_back->validGlobalBound(location)) {
            m_data->stateStack.RemoveState();

        }
    }
}

void AboutState::Update(float)
{
    setVolume(m_data->user.getIfSound());

}

void AboutState::Draw()
{
    m_data->window->draw(m_background);
    m_data->window->draw(*m_back.get());
    m_data->window->draw(m_about);

}


