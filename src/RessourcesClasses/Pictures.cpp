#include <iostream>
#include "Pictures.h"

const std::string Pictures::MarioDriver = "mario.png";
const std::string Pictures::mario_circuit_2 = "mario_circuit_2.png";
const std::string Pictures::misc = "misc.png";
const std::string Pictures::menuBackground = "menuBackground.png";
const std::string Pictures::marioLogo = "marioLogo.png";
const std::string Pictures::letsPlay = "letsPlay.png";
const std::string Pictures::help = "help.png";
const std::string Pictures::about = "about.png";
const std::string Pictures::online = "online.png";
const std::string Pictures::settings = "settings.png";
const std::string Pictures::career = "career.png";
const std::string Pictures::back = "back.png";


Pictures &Pictures::instance() {
    static Pictures inst;
    return inst;
}

Pictures::Pictures() {


    if(!(m_pics[Pictures::MarioDriver] = sf::Texture()).loadFromFile(Pictures::MarioDriver))std::cout<<"Cant Open " + Pictures::MarioDriver;
    if(!(m_maps[Pictures::mario_circuit_2] = sf::Image()).loadFromFile(Pictures::mario_circuit_2))std::cout<<"Cant Open " + Pictures::mario_circuit_2;
    if(!(m_maps[Pictures::misc] = sf::Image()).loadFromFile(Pictures::misc))std::cout<<"Cant Open " + Pictures::misc;
    if(!(m_pics[Pictures::menuBackground] = sf::Texture()).loadFromFile(Pictures::menuBackground))std::cout << "Cant Open " + Pictures::menuBackground;
    if(!(m_pics[Pictures::marioLogo] = sf::Texture()).loadFromFile(Pictures::marioLogo))std::cout << "Cant Open " + Pictures::marioLogo;
    if(!(m_pics[Pictures::letsPlay] = sf::Texture()).loadFromFile(Pictures::letsPlay))std::cout << "Cant Open " + Pictures::letsPlay;
    if(!(m_pics[Pictures::help] = sf::Texture()).loadFromFile(Pictures::help))std::cout << "Cant Open " + Pictures::help;
    if(!(m_pics[Pictures::about] = sf::Texture()).loadFromFile(Pictures::about))std::cout << "Cant Open " + Pictures::about;
    if(!(m_pics[Pictures::online] = sf::Texture()).loadFromFile(Pictures::online))std::cout << "Cant Open " + Pictures::online;
    if(!(m_pics[Pictures::settings] = sf::Texture()).loadFromFile(Pictures::settings))std::cout << "Cant Open " + Pictures::settings;
    if(!(m_pics[Pictures::career] = sf::Texture()).loadFromFile(Pictures::career))std::cout << "Cant Open " + Pictures::career;
    if(!(m_pics[Pictures::back] = sf::Texture()).loadFromFile(Pictures::back))std::cout << "Cant Open " + Pictures::back;

}

const sf::Texture &Pictures::getTexture(std::string name) const {
    return m_pics.at(name);
}

const sf::Image &Pictures::getMapTex(std::string string) {
    return m_maps[string];
}
