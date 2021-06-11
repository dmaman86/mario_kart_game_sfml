#pragma once

#include <SFML/Graphics.hpp>
#include <exception>
#include "Macros.h"

class Fonts
{
public:
    ~Fonts() = default;

    const sf::Font& getFont() const;
    const sf::Font& getFontMario() const;
    static Fonts& instance();

private:
    Fonts();
    Fonts(const Fonts & ) =default;

private:
    sf::Font m_font_game;
    sf::Font m_fontMario;
};


