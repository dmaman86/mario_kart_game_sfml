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
    static  const std::string menuBackground;
    static  const std::string marioLogo;
    static  const std::string letsPlay;
    static  const std::string help;
    static  const std::string about;
    static  const std::string online;
    static  const std::string settings;
    static  const std::string career;
    static  const std::string back;
    static const std::string BowserDriver;
    static const std::string DKDriver;
    static const std::string KoopaDriver;
    static const std::string LuigiDriver;
    static const std::string PeachDriver;
    static const std::string ToadDriver;
    static const std::string YoshiDriver;

    const sf::Texture& getTexture(std::string) const;
    const sf::Image& getMapTex(std::string);


private:
    Pictures();
    Pictures(const Pictures &) = default;
    std::unordered_map<std::string,sf::Texture> m_pics;
    std::unordered_map<std::string,sf::Image> m_maps;



};
