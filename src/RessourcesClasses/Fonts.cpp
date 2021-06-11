#include "Fonts.h"

Fonts::Fonts()
{
    if( !m_font_game.loadFromFile( "font_game.ttf" ) )
        throw std::runtime_error( "can't open font game" );

    if (!m_fontMario.loadFromFile("marioFont.ttf"))
        throw std::runtime_error("can't open font game");
    
}

Fonts &Fonts::instance()
{
    static Fonts inst;
    return inst;
}

const sf::Font& Fonts::getFont() const
{
    return m_font_game;
}

const sf::Font& Fonts::getFontMario() const
{
    return m_fontMario;
}
