#include "Sounds.h"
#include <iostream>
#include <exception>

const std::string Sounds::click = "click.wav";
const std::string Sounds::menu = "menu.ogg";


Sounds &Sounds::instance() {
    static Sounds  inst;
    return inst;
}

const sf::SoundBuffer& Sounds::getSoundBuffer(std::string name) const
{
    return m_sound.at(name);
}

Sounds::Sounds() {

    if (!(m_sound[Sounds::click] = sf::SoundBuffer()).loadFromFile(Sounds::click))
        throw std::runtime_error("Cant Open " + Sounds::click);

    if (!(m_sound[Sounds::menu] = sf::SoundBuffer()).loadFromFile(Sounds::menu))
        throw std::runtime_error("Cant Open " + Sounds::menu);
}
