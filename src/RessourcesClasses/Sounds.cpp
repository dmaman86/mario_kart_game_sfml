#include "Sounds.h"
#include <iostream>
#include <exception>

const std::string Sounds::click = "click.wav";

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
}
