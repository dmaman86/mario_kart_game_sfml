#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>


enum class Direction
{
    Up,
    Down,
    Right,
    Left,
    Stay,
    Max,
};

Direction opposite(Direction dir);
sf::Vector2f toVector(Direction dir);


struct AnimationData
{
//    using ListType = std::vector<sf::IntRect>;
//    using DataType = std::unordered_map<int,ListType>;
//    DataType m_data;
 std::vector <sf::IntRect > m_data;
};
