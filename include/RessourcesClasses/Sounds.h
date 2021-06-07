#pragma once
#include <string>
#include <SFML/Audio.hpp>
//#include <boost\unordered\unordered_map.hpp>
#include <unordered_map>
class Sounds {

public:
    static Sounds& instance();

    static  const std::string click;
    static  const std::string menu;


    const sf::SoundBuffer &getSoundBuffer(std::string) const;

private:

    Sounds() ;
    Sounds(const Sounds&) = default;
    std::unordered_map<std::string, sf::SoundBuffer> m_sound;
    int m_volume = 100;
};

