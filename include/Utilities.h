#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "iostream"
#include "fstream"

const float calcLength(const sf::Vector2f a, const  sf::Vector2f b);

// calc the sinus of the number and return the value in degrees
float calcSinDegree(float m_angle );

// calc the cosinus of the number and return the value in degrees
float calcCosDegree(float m_angle );

template <class T>
std::vector<std::vector<T>> readFromFile(std::string str){

    std::vector<std::vector <T>> map_int;
    std::ifstream m_file(str);
    T input;
    if (!m_file.is_open())
        throw std::range_error("cannot open m_file");
    for (int i = 0; i < 128; ++i)
    {
        std::vector<T> row;
        for (int j = 0; j < 128; ++j)
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
