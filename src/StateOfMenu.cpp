#include "StateOfMenu.h"
#include "Pictures.h"


void StateOfMenu::InitOfMenu(MarioKart::GameDataRef data)
{
    sf::Vector2u textureSize;
    m_windowSize = data->window->getSize();
    textureSize = Pictures::instance().getTexture(Pictures::menuBackground).getSize();

    m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
    m_background.setScale((float)m_windowSize.x / textureSize.x,
        (float)m_windowSize.y / textureSize.y);
    m_back.setTexture(Pictures::instance().getTexture(Pictures::back));

}
