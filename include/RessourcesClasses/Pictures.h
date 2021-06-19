#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <string>


const int DRIVER_VECTOR_LEN = 12;
const int NUMBER_OF_DRIVERS = 8;
const int DRIVER_SIDE_LEN = 6;
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
    static const std::string donut_plains_1;
    static  const std::string misc;
    static  const std::string menuBackground;
    static  const std::string marioLogo;
    static  const std::string help;
    static  const std::string about;
    static  const std::string back;
    static const std::string BowserDriver;
    static const std::string DKDriver;
    static const std::string KoopaDriver;
    static const std::string LuigiDriver;
    static const std::string PeachDriver;
    static const std::string ToadDriver;
    static const std::string YoshiDriver;
    static const std::string rectangle;
	static const std::string sky_back;
	static const std::string sky_front;
	static const std::string speed0;
	static const std::string speed1;
	static const std::string speed2;
	static const std::string speed3;
	static const std::string speed4;
    static const std::string MenuButtons1;
    static const std::string GameStartGui;
    static const std::string helpStateback;
	static const std::string game_boy;

    const sf::Texture& getTexture(const std::string &) const;
    const sf::Image& getMapTex(const std::string &)const ;
    const std::vector <sf::IntRect>& getDriveAnimationData(const std::string &)const;


    const std::vector<sf::IntRect>& getTraffic()const;
    const std::vector<sf::IntRect>& getCloud()const;


private:
    Pictures();
    Pictures(const Pictures &) = default;
    std::unordered_map<std::string,sf::Texture> m_pics;
    std::unordered_map<std::string,sf::Image> m_maps;
    std::vector <sf::IntRect> setDriverData(int i);
    std::vector<sf::IntRect> m_trafficLight;
    std::vector<sf::IntRect> m_startCloud;
    std::vector <std::vector<sf::IntRect >> m_drivers;


};
