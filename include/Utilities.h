#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "iostream"
#include "fstream"
#include "Macros.h"

const auto PIE = 3.141592f;
const auto DEG_180 = 180.f;
const auto DEG_360 = 360.0;

const float calcLength(const sf::Vector2f, const sf::Vector2f);

// calc the sinus of the number and return the value in degrees
const float calcSinDegree(const float);

// calc the cosinus of the number and return the value in degrees
const float calcCosDegree(const float);

template <class T>
std::vector<std::vector<T>> readFromFile
	(const std::string str,const int sizex = DimensionGame::DEF_SIZE, const int sizey = DimensionGame::DEF_SIZE)
{
    std::vector<std::vector <T>> map_int;
    std::ifstream m_file(str);
    T input;
    if (!m_file.is_open())
        throw std::range_error("cannot open "+ str +"file");
    for (int i = 0; i < sizex; ++i)
    {
        std::vector<T> row;
        for (int j = 0; j < sizey; ++j)
        {
            m_file >> input;
            row.push_back(input);
        }
        m_file.get();
        map_int.push_back(row);
    }
    m_file.close();


    return map_int;
}
