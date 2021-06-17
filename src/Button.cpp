#include "Button.h"
#include "Pictures.h"

Button::Button( const std::string& sprite_name)
    : m_button(Pictures::instance().getTexture(sprite_name)),
      m_id(),
      m_name(sprite_name),
      m_selected(false)
{

}

Button::Button(const std::string &id, const std::string &name)
    : m_id(id),
      m_button(Pictures::instance().getTexture(name))
{

}

bool Button::validGlobalBound(const sf::Vector2f& location)
{
    return m_button.getGlobalBounds().contains(location);
}

void Button::setTextureInRect( int x, int y, int z, int w )
{
    m_button.setTextureRect(sf::Rect(x, y, z, w));
}

void Button::setInScale(float x, float y)
{
    m_button.scale( x, y );
}

void Button::setIntoScale(float x, float y)
{
    m_button.setScale(x, y);
}

void Button::setInPosition( const sf::Vector2f& position )
{
    m_button.setPosition(position);
}

/*void Button::draw( sf::RenderWindow* window )
{
    window->draw(m_button);
}*/

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_button);
}

void Button::setCallback(Callback callback)
{
    m_callBack = callback;
}

void Button::initCallback()
{
    if(m_callBack)
        m_callBack();
}
