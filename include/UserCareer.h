#pragma once

#include <string>
#include <vector>
#include "SFML/Graphics.hpp"

class UserCareer
{
public:
    UserCareer(std::string name, std::string coins, std::vector<std::string>);
    ~UserCareer() = default;

    const std::string& getName()const { return m_name;};
    const int getCoins()const { return m_numberCoins;}; 

private:
    void setName(std::string);
    void setCoins(int);


    std::string m_name;
    int m_numberCoins;
    std::vector<std::string> m_drivers;
    bool m_sound;
    bool m_music;
};