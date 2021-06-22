#include "Sounds.h"
#include <iostream>
#include <exception>

const std::string Sounds::click = "click.wav";
const std::string Sounds::menu = "menu.ogg";
const std::string Sounds::vanillaLakeMap = "vanillaLakeMap.ogg";
const std::string Sounds::coin = "coin.wav";
const std::string Sounds::boost = "boost.wav";
const std::string Sounds::banana = "banana.wav";
const std::string Sounds::pipe = "pipe.wav";
const std::string Sounds::startGame = "startGame.wav";
const std::string Sounds::ghost = "ghost.wav";
const std::string Sounds::sand = "sand.wav";
const std::string Sounds::lose = "lose.wav";
const std::string Sounds::win = "win.wav";


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

   /* if (!(m_sound[Sounds::menu] = sf::SoundBuffer()).loadFromFile(Sounds::menu))
        throw std::runtime_error("Cant Open " + Sounds::menu);*/

    if (!(m_sound[Sounds::coin] = sf::SoundBuffer()).loadFromFile(Sounds::coin))
        throw std::runtime_error("Cant Open " + Sounds::coin);

    if (!(m_sound[Sounds::boost] = sf::SoundBuffer()).loadFromFile(Sounds::boost))
        throw std::runtime_error("Cant Open " + Sounds::boost);

    if (!(m_sound[Sounds::banana] = sf::SoundBuffer()).loadFromFile(Sounds::banana))
        throw std::runtime_error("Cant Open " + Sounds::banana);

    if (!(m_sound[Sounds::pipe] = sf::SoundBuffer()).loadFromFile(Sounds::pipe))
        throw std::runtime_error("Cant Open " + Sounds::pipe);

    if (!(m_sound[Sounds::startGame] = sf::SoundBuffer()).loadFromFile(Sounds::startGame))
        throw std::runtime_error("Cant Open " + Sounds::startGame);

    if (!(m_sound[Sounds::ghost] = sf::SoundBuffer()).loadFromFile(Sounds::ghost))
        throw std::runtime_error("Cant Open " + Sounds::ghost);

    if (!(m_sound[Sounds::sand] = sf::SoundBuffer()).loadFromFile(Sounds::sand))
        throw std::runtime_error("Cant Open " + Sounds::sand);

    if (!(m_sound[Sounds::lose] = sf::SoundBuffer()).loadFromFile(Sounds::lose))
        throw std::runtime_error("Cant Open " + Sounds::lose);

    if (!(m_sound[Sounds::win] = sf::SoundBuffer()).loadFromFile(Sounds::win))
        throw std::runtime_error("Cant Open " + Sounds::win);
}
