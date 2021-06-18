#include "GarageState.h"
#include "Pictures.h"
#include "Fonts.h"
GarageState::GarageState(MarioKart::GameDataRef& data):m_data(data), StateOfMenu(data)
{

}

void GarageState::Init()
{
    sf::Vector2u windowSize;
    windowSize = m_data->window->getSize();
    initVectorSprites(windowSize);

    m_back->setCallback([this](){
        m_data->stateStack.RemoveState();
    });
    m_buttons[Options::Back] = m_back;
}

void GarageState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type)
    {
        m_click.play();
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseButton.x, event.mouseButton.y });

        for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
        {
            if( auto res = it->second->validGlobalBound(location); res)
            {
                it->second->updateIfSelected(res);
                resetButtons(it->first);
                break;
            }
        }
    }
}

void GarageState::Update(float )
{

    setVolume(m_data->user.getIfSound());
    for( auto it = m_buttons.begin(); it != m_buttons.end(); it++)
    {
        switch (it->first)
        {
            case Options::Back:
                if(it->second->getIfSelected())
                    it->second->initCallback();
                break;
        }
    }
}

void GarageState::Draw()
{
    m_data->window->draw(m_background);
    for (auto it : m_buttons)
        m_data->window->draw(*it.second.get());

    for (auto driver : m_drivers)
    {
        m_data->window->draw(driver.first);
        m_data->window->draw(driver.second);
    }

}

void GarageState::resetButtons(Options option)
{
    for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
    {
        if(it->first != option)
            it->second->resetIfSelected();
    }
}

void GarageState::initVectorSprites(const sf::Vector2u& windowSize)
{

    m_drivers.emplace_back(std::pair(Button(Pictures::drivers), sf::Text("1000" ,Fonts::instance().Fonts::getFontMario())));
    m_drivers.emplace_back(std::pair(Button(Pictures::drivers), sf::Text("1000", Fonts::instance().Fonts::getFontMario())));
    m_drivers.emplace_back(std::pair(Button(Pictures::drivers), sf::Text("1000", Fonts::instance().Fonts::getFontMario())));
    m_drivers.emplace_back(std::pair(Button(Pictures::drivers), sf::Text("1000", Fonts::instance().Fonts::getFontMario())));
    m_drivers.emplace_back(std::pair(Button(Pictures::drivers), sf::Text("1000", Fonts::instance().Fonts::getFontMario())));
    m_drivers.emplace_back(std::pair(Button(Pictures::drivers), sf::Text("1000", Fonts::instance().Fonts::getFontMario())));
    m_drivers.emplace_back(std::pair(Button(Pictures::drivers), sf::Text("1000", Fonts::instance().Fonts::getFontMario())));
    m_drivers.emplace_back(std::pair(Button(Pictures::drivers), sf::Text("1000", Fonts::instance().Fonts::getFontMario())));

    size_t i = 0;
    size_t j = 5;
    for (auto it = m_drivers.begin(); it != m_drivers.end(); it++, i += 5, j+=35)
    {
       
        it->first.setTextureInRect(360, j, 33, 30);
        it->first.setInScale(3, 4);
        it->first.setInPosition(sf::Vector2f(120 + (i * 30), (it->first.getWidth() / 2) + 150));


        it->second.setColor(sf::Color::Blue);
        it->second.setPosition(sf::Vector2f(120 + (i * 30), (it->first.getWidth() / 2) + 300));


    }
}
