#include "Button.h"
#include "Pictures.h"

//========================== Constructor ==============================
Button::Button( const std::string& sprite_name)
    : m_button(Pictures::instance().getTexture(sprite_name)),
      m_id(),
      m_name(sprite_name),
      m_selected(false)
{

}

//========================= Constructor ==============================
Button::Button(const std::string &id, const std::string &name)
    : m_id(id),
      m_button(Pictures::instance().getTexture(name))
{

}

//=======================================================================
bool Button::validGlobalBound(const sf::Vector2f& location)
{
    return m_button.getGlobalBounds().contains(location);
}

//=======================================================================
void Button::setTextureInRect( const sf::IntRect& var )
{
    m_button.setTextureRect(var);
}

//=======================================================================
void Button::setTextureInRect( int x, int y, int z, int w )
{
    m_button.setTextureRect(sf::Rect(x, y, z, w));
}

//=======================================================================
void Button::setInScale(float x, float y)
{
    m_button.scale( x, y );
}

//=======================================================================
void Button::setIntoScale(float x, float y)
{
    m_button.setScale(x, y);
}

//=======================================================================
void Button::setInPosition( const sf::Vector2f& position )
{
    m_button.setPosition(position);
}

//=======================================================================
void Button::updateIfSelected(bool selected)
{
    m_selected = selected;
}

//=======================================================================
void Button::resetIfSelected()
{
    m_selected = false;
}

//=======================================================================
const sf::Vector2f& Button::getInPosition()
{
    return m_button.getPosition();
}

//=======================================================================
void Button::setInOrigin()
{
    m_button.setOrigin(m_button.getLocalBounds().width / 2,
                       m_button.getLocalBounds().height / 2);
}

//=======================================================================
void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_button);
}

//=======================================================================
void Button::setCallback(Callback callback)
{
    m_callBack = callback;
}

//=======================================================================
void Button::initCallback()
{
    if(m_callBack)
        m_callBack();
}

//=======================================================================
float Button::getWidth()
{
    return m_button.getGlobalBounds().width;
}

//=======================================================================
float Button::getHeight()
{
    return m_button.getGlobalBounds().height;
}

//=======================================================================
const std::string& Button::getName()
{
    return m_name;
}

//=======================================================================
void Button::setId(const std::string& id)
{
    m_id = id;
}

//=======================================================================
const std::string& Button::getId()
{
    return m_id;
}

//=======================================================================
const bool& Button::getIfSelected()
{
    return m_selected;
}

//=======================================================================
void Button::setFillInColor(sf::Color color)
{
    m_button.setColor(color);
}

//=======================================================================
const sf::Sprite& Button::getSprite()
{
    return m_button;
}
