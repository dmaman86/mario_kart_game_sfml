#include <iostream>
#include "Pictures.h"

const std::string Pictures::MarioDriver = "mario.png";
const std::string Pictures::mario_circuit_2 = "mario_circuit_2.png";
const std::string Pictures::misc = "misc.png";



Pictures &Pictures::instance() {
    static Pictures inst;
    return inst;
}

Pictures::Pictures() {


    if(!(m_pics[Pictures::MarioDriver] = sf::Texture()).loadFromFile(Pictures::MarioDriver))std::cout<<"Cant Open " + Pictures::MarioDriver;
    if(!(m_maps[Pictures::mario_circuit_2] = sf::Image()).loadFromFile(Pictures::mario_circuit_2))std::cout<<"Cant Open " + Pictures::mario_circuit_2;
    if(!(m_maps[Pictures::misc] = sf::Image()).loadFromFile(Pictures::misc))std::cout<<"Cant Open " + Pictures::misc;

}

const sf::Texture &Pictures::getTexture(std::string name) {
    return m_pics[name];
}

const sf::Image &Pictures::getMapTex(std::string string) {
    return m_maps[string];
}
