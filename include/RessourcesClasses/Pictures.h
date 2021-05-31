#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <string>
class Pictures{

public:

    static Pictures& instance();

    static  const std::string MarioDriver;
    static  const std::string mario_circuit_2;
    static  const std::string misc;

    const sf::Texture& getTexture(std::string);
    const sf::Image& getMapTex(std::string);


private:
    Pictures();
    Pictures(const Pictures &) = default;
    std::unordered_map<std::string,sf::Texture> m_pics;
    std::unordered_map<std::string,sf::Image> m_maps;



};
