#include "GarageState.h"
#include "Pictures.h"
#include "Fonts.h"
GarageState::GarageState(MarioKart::GameDataRef& data):m_data(data), StateOfMenu(data), m_selectCar()
{
    
}

void GarageState::Init()
{
    sf::Vector2u windowSize;
    windowSize = m_data->window->getSize();
    initVectorSprites(windowSize);


    m_msg.emplace_back(std::pair(sf::Text("Press Enter if you want to buy", Fonts::instance().Fonts::getFontMario()), false));
    m_msg.back().first.setColor(sf::Color::Blue);
    m_msg.emplace_back(std::pair(sf::Text("The car was successfully purchased", Fonts::instance().Fonts::getFontMario()), false));
    m_msg.back().first.setColor(sf::Color::Green);
    m_msg.emplace_back(std::pair(sf::Text("you do not have enough money", Fonts::instance().Fonts::getFontMario()), false));
    m_msg.back().first.setColor(sf::Color::Red);

    for (auto& msg : m_msg)
    {
        msg.first.setOutlineThickness(5.f);
        msg.first.setPosition(windowSize.x / (unsigned)2.5, 500);
        msg.first.setOrigin(msg.first.getLocalBounds().width / 2,
            msg.first.getLocalBounds().height / 2);
        msg.first.setScale(2, 2);
    }
   


    m_back->setCallback([this](){
        m_data->stateStack.RemoveState();
    });
    m_buttons[Options::Back] = m_back;

    for (int i = 0; i < m_data->user.getMaxDrivers(); ++i)
    {
        m_drivers.at(m_data->user.getDrive(i)).buy = false;
        m_drivers.at(m_data->user.getDrive(i)).price.setColor(sf::Color::Red);
    }
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

        for (auto& it : m_drivers)
        {
            updateColors(location);       
            
        }
    }
    if (event.type == sf::Event::TextEntered)
    {
        // if press on drivers
        if (m_msg[0].second)
        {
            buyingTest(m_selectCar);
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
        m_data->window->draw(driver.second.sprite);
        m_data->window->draw(driver.second.price);
    }

    for (auto msg : m_msg)
    {
        if(msg.second)
            m_data->window->draw(msg.first);
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


    m_drivers.emplace(std::make_pair(Pictures::BowserDriver, driver(true, (Pictures::drivers), sf::Text("1000", Fonts::instance().Fonts::getFontMario()))));
    m_drivers.emplace(std::make_pair(Pictures::DKDriver,     driver(true, (Pictures::drivers), sf::Text("1000", Fonts::instance().Fonts::getFontMario()))));
    m_drivers.emplace(std::make_pair(Pictures::MarioDriver,  driver(true, (Pictures::drivers), sf::Text("1000", Fonts::instance().Fonts::getFontMario()))));
    m_drivers.emplace(std::make_pair(Pictures::KoopaDriver,  driver(true, (Pictures::drivers), sf::Text("1000", Fonts::instance().Fonts::getFontMario()))));
    m_drivers.emplace(std::make_pair(Pictures::LuigiDriver,  driver(true, (Pictures::drivers), sf::Text("1000", Fonts::instance().Fonts::getFontMario()))));
    m_drivers.emplace(std::make_pair(Pictures::PeachDriver,  driver(true, (Pictures::drivers), sf::Text("1000", Fonts::instance().Fonts::getFontMario()))));
    m_drivers.emplace(std::make_pair(Pictures::ToadDriver,   driver(true, (Pictures::drivers), sf::Text("1000", Fonts::instance().Fonts::getFontMario()))));
    m_drivers.emplace(std::make_pair(Pictures::YoshiDriver,  driver(true, (Pictures::drivers), sf::Text("1000", Fonts::instance().Fonts::getFontMario()))));


    size_t i = 0;
    size_t j = 5;
    for (auto it = m_drivers.begin(); it != m_drivers.end(); it++, i += 5, j += 35)
    {

        it->second.sprite.setTextureInRect(360, j, 33, 33);
        it->second.sprite.setInScale(3, 4);
        it->second.sprite.setInPosition(sf::Vector2f(120 + (i * 30), (it->second.sprite.getWidth() / 2) + 150));

        it->second.price.setColor(sf::Color::Blue);
        it->second.price.setPosition(sf::Vector2f(120 + (i * 30), (it->second.sprite.getWidth() / 2) + 300));


    }
}

void GarageState::updateColors(const sf::Vector2f loc)
{
    for (auto& button : m_drivers)
    {

        button.second.sprite.setFillInColor(255, 255, 255, 250);

        if (button.second.sprite.validGlobalBound(loc))
        {
            button.second.sprite.setFillInColor(255, 255, 255, 130);
            if (!button.second.buy)
            {
                m_data->user.setSprite(button.first);
                m_msg[0].second = false;
                m_msg[1].second = false;
                m_msg[2].second = false;
            }
            else
            {
                m_msg[0].second = true;
                m_msg[1].second = false;
                m_msg[2].second = false;
                m_selectCar = button.first;
            }
        }
    }
}

void GarageState::buyingTest(std::string car)
{
   std::string price =(m_drivers.at(car).price.getString());
   if (std::stoi(price) <= m_data->user.getCoins())
   {
       m_msg[1].second = true;
       m_data->user.setDrive(car);
       m_data->user.setSprite(car);
       m_data->user.setCoins(m_data->user.getCoins() - std::stoi(price));
   }
   else
   {
       m_msg[2].second = true;
   }
   m_msg[0].second = false;

}
