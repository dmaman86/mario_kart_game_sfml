#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <string>
#include "AnimationData.h"


const int DRIVER_VECTOR_LEN = 6;
const int NUMBER_OF_DRIVERS = 6;
enum  Drivers{
    Boewser,
    Dk,
    Mario,
    Koopa,
    Luigi,
    Peach,
    Toad,
    Yoshi
};
class Pictures{

public:

    static Pictures& instance();
    static  const std::string drivers;

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
	static  const std::string new_game;
	static  const std::string load_game;
    static const std::string BowserDriver;
    static const std::string DKDriver;
    static const std::string KoopaDriver;
    static const std::string LuigiDriver;
    static const std::string PeachDriver;
    static const std::string ToadDriver;
    static const std::string YoshiDriver;
    static const std::string rectangle;

    const sf::Texture& getTexture(std::string) const;
    const sf::Image& getMapTex(std::string);
    const AnimationData& getDriveAnimationData(std::string);

    std::vector<AnimationData> m_drivers;

private:
    Pictures();
    Pictures(const Pictures &) = default;
    std::unordered_map<std::string,sf::Texture> m_pics;
    std::unordered_map<std::string,sf::Image> m_maps;
    AnimationData setDriverData(int i);
};
