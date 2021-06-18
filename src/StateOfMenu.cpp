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
    m_back->setTextureInRect(0, 563, 180, 63);

    //sound
    m_click.setBuffer(Sounds::instance().getSoundBuffer(Sounds::click));

}

void StateOfMenu::setVolume(bool data)
{
    if (data)
        m_click.setVolume(100);
    else
        m_click.setVolume(0);
}
