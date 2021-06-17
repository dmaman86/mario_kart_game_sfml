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



    m_buttons.emplace_back(m_back);
    m_buttons.back().setCallback([this]() {
        m_data->stateStack.RemoveState();
        });

}

void GarageState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type)
    {
        m_click.play();
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseButton.x, event.mouseButton.y });

        for (size_t i{ 0 }; i < m_buttons.size(); i++)
        {
            if (auto res = m_buttons[i].validGlobalBound(location); res)
            {
                m_buttons[i].updateIfSelected(res);
                resetButtons(i);
                break;
            }
        }
    }
}

void GarageState::Update(float )
{

    setVolume(m_data->user.getIfSound());

    for (size_t i{ 0 }; i < m_buttons.size(); i++)
    {
        switch (i)
        {
        case 0:
        {
            if (m_buttons[0].getIfSelected())//if pres back
                m_buttons[0].initCallback();
            break;
        }
        
      
        }
    }

   
}

void GarageState::Draw()
{
    m_data->window->draw(m_background);
    for (auto it : m_buttons)
        m_data->window->draw(it);

    for (auto driver : m_drivers)
    {
        m_data->window->draw(driver.first);
        m_data->window->draw(driver.second);
    }

}

void GarageState::resetButtons(size_t index)
{
    for (size_t i{ 0 }; i < m_buttons.size(); i++)
    {
        if (i != index)
            m_buttons[i].resetIfSelected();
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
