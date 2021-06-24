#include "StateOfMenu.h"
#include "Pictures.h"
#include "Sounds.h"

StateOfMenu::StateOfMenu(MarioKart::GameDataRef data)
{
    InitOfMenu(data);
}

void StateOfMenu::InitOfMenu(MarioKart::GameDataRef data)
{
    sf::Vector2u textureSize;
    m_windowSize = data->window->getSize();
    //background
    textureSize = Pictures::instance().getTexture(Pictures::menuBackground).getSize();
    m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
    m_background.setScale((float)m_windowSize.x / textureSize.x,
        (float)m_windowSize.y / textureSize.y);

    m_back = std::make_shared<Button>(Pictures::MenuButtons1);
    m_back->setTextureInRect(PositionButtons::back);

    //sound
    m_click.setBuffer(Sounds::instance().getSoundBuffer(Sounds::click));
    m_logo = sf::Sprite();
    m_logo.setTexture(Pictures::instance().getTexture(Pictures::MenuButtons1));
    m_logo.setTextureRect(sf::Rect(0, 410, 250, 63));
    m_logo.setOrigin(m_logo.getGlobalBounds().width / 2.f, m_logo.getGlobalBounds().height /2.f );
    m_logo.setPosition(float(m_windowSize.x / 2), float(m_windowSize.y / 2) + 370.f);
}

void StateOfMenu::setVolume(bool sound)
{
    m_soundOn = sound;
}
