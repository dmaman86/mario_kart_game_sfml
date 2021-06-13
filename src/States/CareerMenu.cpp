#include "CareerMenu.h"
#include "Pictures.h"
#include "MenuState.h"
#include "GetDataState.h"
#include "Fonts.h"
CareerMenu::CareerMenu(MarioKart::GameDataRef& data): m_data(data),
                                                        m_backMenu(false),
                                                        m_background()
{
}

void CareerMenu::Init()
{
    sf::Vector2u textureSize, windowSize;
    windowSize = m_data->window->getSize();
    textureSize = Pictures::instance().getTexture(Pictures::menuBackground).getSize();

    m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
    m_background.setScale((float)windowSize.x / textureSize.x,
                          (float)windowSize.y / textureSize.y);

    m_time.setTexture(Pictures::instance().getTexture(Pictures::MenuButtons));
    m_coin.setTexture(Pictures::instance().getTexture(Pictures::MenuButtons));
    m_dk.setTexture(Pictures::instance().getTexture(Pictures::MenuButtons));
    m_garage.setTexture(Pictures::instance().getTexture(Pictures::MenuButtons));

    m_time.setTextureRect(sf::Rect(38,4,456,77));
    m_coin.setTextureRect(sf::Rect(50,70,600,100));
    m_dk.setTextureRect(sf::Rect(30,220,494,66));
    m_garage.setTextureRect(sf::Rect(30,350,400,85));

    m_time.setPosition(250,250);
    m_coin.setPosition(250,325);
   m_dk.setPosition(250,450);
   m_garage.setPosition(250,570);

   m_driver.setTexture(Pictures::instance().getTexture(Pictures::instance().drivers));
   m_driver.setTextureRect(sf::Rect(132,80,37,34));
   m_driver.setOrigin(m_driver.getGlobalBounds().width/2,m_driver.getGlobalBounds().height/2);
   m_driver.scale(-10,10);
   m_driver.setPosition(1200,500);
    m_click.setBuffer(Sounds::instance().getSoundBuffer(Sounds::click));
    m_name.setFont(Fonts::instance().Fonts::getFontMario());
    m_moneys.setFont(Fonts::instance().Fonts::getFontMario());
    m_car.setFont(Fonts::instance().Fonts::getFontMario());

    m_name.setString("Liran");
    m_moneys.setString("10000$");
    m_car.setString("Mario Mother fucker");


    m_name.setPosition(1450,250);
    m_moneys.setPosition(1450,350);
    m_car.setPosition(1450,450);

}

void CareerMenu::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type) {
        m_click.play();
        auto location = m_data->window->mapPixelToCoords(
                { event.mouseButton.x, event.mouseButton.y });
        if (m_back.getGlobalBounds().contains(location)) {
            m_backMenu = true;
        }
        if (m_time.getGlobalBounds().contains(location)) {
            m_data->stateStack.AddState(StateStack::StateRef(new GetDataState(m_data)),
                                        false);
        }
        if (m_coin.getGlobalBounds().contains(location)) {
            m_data->stateStack.AddState(StateStack::StateRef(new GetDataState(m_data)),false);
        }
        if (m_dk.getGlobalBounds().contains(location)) {
            m_data->stateStack.AddState(StateStack::StateRef(new GetDataState(m_data)),false);
        }
        if (m_garage.getGlobalBounds().contains(location)) {
            m_data->stateStack.AddState(StateStack::StateRef(new GetDataState(m_data)),false);
        }


    }
}

void CareerMenu::Update(float)
{
    setVolume();
    if (m_backMenu)
    {
        m_data->stateStack.RemoveState();
    }
}

void CareerMenu::Draw()
{

    m_data->window->draw(m_background);
    m_data->window->draw(m_back);
    m_data->window->draw(m_coin);
    m_data->window->draw(m_garage);
    m_data->window->draw(m_time);
    m_data->window->draw(m_dk);
    m_data->window->draw(m_driver);
    m_data->window->draw(m_name);
    m_data->window->draw(m_moneys);
    m_data->window->draw(m_car);


}

void CareerMenu::setVolume()
{
    if(m_data->user.getIfSound())
        m_click.setVolume(100);
    else
        m_click.setVolume(0);
}

