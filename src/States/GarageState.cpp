#include "GarageState.h"
#include "Pictures.h"
#include "Fonts.h"

GarageState::GarageState(MarioKart::GameDataRef& data): m_data(data),
                                                        StateOfMenu(data),
                                                        m_selectCar()
{
    
}
//init the state 
//=============================================================
void GarageState::Init()
{
    sf::Vector2u windowSize;
    windowSize = m_data->window->getSize();
    initVectorSprites();

    createText(windowSize);

    m_back->setCallback([this](){
        m_data->stateStack.RemoveState();
    });
    m_buttons[Options::Back] = m_back;

    blockingMyPlayers();
}

//=============================================================
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

        updateColors(location);
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

//update the state 
//update my coins and the driver if I'm buy
//=============================================================
void GarageState::Update(const float )
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

    m_numberCoins.setString("my coins:" + std::to_string(m_data->user.getCoins()));

    blockingMyPlayers();
}

//draw thw object
//=============================================================
void GarageState::Draw()
{
    m_data->window->draw(m_background);
    m_data->window->draw(m_logo);
    for (auto it : m_buttons)
        m_data->window->draw(*it.second.get());

    for (auto &driver : m_drivers)
    {
        m_data->window->draw(driver.second.sprite);
        m_data->window->draw(driver.second.price);
    }

    for (auto msg : m_msg)
    {
        if(msg.second)
            m_data->window->draw(msg.first);
    }
    m_data->window->draw(m_numberCoins);

}

//reset the buttons
//=============================================================
void GarageState::resetButtons(Options option)
{
    for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
    {
        if(it->first != option)
            it->second->resetIfSelected();
    }
}

//create object in map of price , sprite and bool if i buy the drivers
//=============================================================
void GarageState::initVectorSprites()
{

    int i = -5;
    m_drivers.emplace(std::make_pair(Pictures::BowserDriver, driver(true, (Pictures::drivers), sf::Text("1000", Fonts::instance().Fonts::getFontMario()))));
    m_drivers.at(Pictures::BowserDriver).sprite.setTextureInRect(PositionDrivers::bowser);
    initDriver(m_drivers.at(Pictures::BowserDriver), i+=5);

    m_drivers.emplace(std::make_pair(Pictures::DKDriver, driver(true, (Pictures::drivers), sf::Text("1200", Fonts::instance().Fonts::getFontMario()))));
    m_drivers.at(Pictures::DKDriver).sprite.setTextureInRect(PositionDrivers::dk);
    initDriver(m_drivers.at(Pictures::DKDriver), i += 5);

    m_drivers.emplace(std::make_pair(Pictures::MarioDriver,  driver(true, (Pictures::drivers), sf::Text("1300", Fonts::instance().Fonts::getFontMario()))));
    m_drivers.at(Pictures::MarioDriver).sprite.setTextureInRect(PositionDrivers::mario);
    initDriver(m_drivers.at(Pictures::MarioDriver), i += 5);

    m_drivers.emplace(std::make_pair(Pictures::KoopaDriver,  driver(true, (Pictures::drivers), sf::Text("1400", Fonts::instance().Fonts::getFontMario()))));
    m_drivers.at(Pictures::KoopaDriver).sprite.setTextureInRect(PositionDrivers::koopa);
    initDriver(m_drivers.at(Pictures::KoopaDriver), i += 5);

    m_drivers.emplace(std::make_pair(Pictures::LuigiDriver,  driver(true, (Pictures::drivers), sf::Text("1500", Fonts::instance().Fonts::getFontMario()))));
    m_drivers.at(Pictures::LuigiDriver).sprite.setTextureInRect(PositionDrivers::luigi);
    initDriver(m_drivers.at(Pictures::LuigiDriver), i += 5);

    m_drivers.emplace(std::make_pair(Pictures::PeachDriver,  driver(true, (Pictures::drivers), sf::Text("1600", Fonts::instance().Fonts::getFontMario()))));
    m_drivers.at(Pictures::PeachDriver).sprite.setTextureInRect(PositionDrivers::peach);
    initDriver(m_drivers.at(Pictures::PeachDriver), i += 5);

    m_drivers.emplace(std::make_pair(Pictures::ToadDriver,   driver(true, (Pictures::drivers), sf::Text("1700", Fonts::instance().Fonts::getFontMario()))));
    m_drivers.at(Pictures::ToadDriver).sprite.setTextureInRect(PositionDrivers::toad);
    initDriver(m_drivers.at(Pictures::ToadDriver), i += 5);

    m_drivers.emplace(std::make_pair(Pictures::YoshiDriver,  driver(true, (Pictures::drivers), sf::Text("1800", Fonts::instance().Fonts::getFontMario()))));
    m_drivers.at(Pictures::YoshiDriver).sprite.setTextureInRect(PositionDrivers::yoshi);
    initDriver(m_drivers.at(Pictures::YoshiDriver), i += 5);

}

//take the pictures of the drivers
//=============================================================
void GarageState::initDriver(driver& dr,const int i)
{
    dr.sprite.setInScale(3, 4);
    dr.sprite.setInPosition(sf::Vector2f(120.f + (float(i) * 30.f), (dr.sprite.getWidth() / 2.f) + 150.f));

    dr.price.setFillColor(sf::Color::Blue);
    dr.price.setPosition(sf::Vector2f(120.f + (float(i) * 30.f), (dr.sprite.getWidth() / 2.f) + 300.f));

}
//=============================================================

void GarageState::blockingMyPlayers()
{
    for (int i = 0; i < m_data->user.getMaxDrivers(); ++i)
    {
        m_drivers.at(m_data->user.getDrive(i)).buy = false;
        m_drivers.at(m_data->user.getDrive(i)).price.setFillColor(sf::Color::Red);
    }
}


//=============================================================
void GarageState::createText(const sf::Vector2u windowSize)
{
    m_msg.emplace_back(std::pair(sf::Text("Press Enter if you want to buy", Fonts::instance().Fonts::getFontMario()), false));
    m_msg.back().first.setFillColor(sf::Color::Blue);
    m_msg.emplace_back(std::pair(sf::Text("The car was successfully purchased", Fonts::instance().Fonts::getFontMario()), false));
    m_msg.back().first.setFillColor(sf::Color::Green);
    m_msg.emplace_back(std::pair(sf::Text("you do not have enough money", Fonts::instance().Fonts::getFontMario()), false));
    m_msg.back().first.setFillColor(sf::Color::Red);

    for (auto& msg : m_msg)
    {
        msg.first.setOutlineThickness(5.f);
        msg.first.setPosition(float(windowSize.x) / 2.5f, 500.f);
        msg.first.setOrigin(msg.first.getLocalBounds().width / 2,
            msg.first.getLocalBounds().height / 2.f);
        msg.first.setScale(2, 2);
    }

    m_numberCoins = sf::Text("my coins:" + std::to_string(m_data->user.getCoins()), Fonts::instance().Fonts::getFontMario(),50);
    m_numberCoins.setPosition(1000, 100);
    m_numberCoins.setFillColor(sf::Color::White);
    m_numberCoins.setOutlineThickness(5.f);

}

//update color in the dreviers if i put the mouse
//=============================================================
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

//check if i can buy 
//=============================================================
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


