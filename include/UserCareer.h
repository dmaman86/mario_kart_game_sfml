#pragma once

#include <string>
#include <vector>
#include "SFML/Graphics.hpp"

class UserCareer
{
public:
    UserCareer() = default;
    UserCareer(std::string name, std::string coins, std::vector<std::string>);
    ~UserCareer() = default;

    const std::string& getName()const { return m_name;};
    const int getCoins()const { return m_numberCoins;}; 
    void setName(std::string name) { m_name = name; };
    void setCoins(int coins) { m_numberCoins = coins; };

private:
   
    std::string m_name;
    int m_numberCoins;
    std::vector<std::string> m_drivers;
    bool m_sound;
    bool m_music;
};