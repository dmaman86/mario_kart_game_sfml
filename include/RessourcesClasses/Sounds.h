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
    static  const std::string coin;
    static  const std::string boost;
    static  const std::string banana;
    static  const std::string pipe;
    static  const std::string startGame;
    static  const std::string ghost;
    static  const std::string sand;
    static  const std::string lose;
    static  const std::string win;



    const sf::SoundBuffer &getSoundBuffer(std::string) const;

private:

    Sounds() ;
    Sounds(const Sounds&) = default;
    std::unordered_map<std::string, sf::SoundBuffer> m_sound;
    int m_volume = 100;
};

