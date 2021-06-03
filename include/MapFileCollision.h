#pragma once
#include <string>
#include <vector>
#include <map>
#include "GameObj.h"
#include <algorithm>
class MapFileCollision {
public:

MapFileCollision();
void fillMap(const std::string);
void fillObjectMap(const std::string);
int operator()(unsigned int,unsigned int);
float calcLength(sf::Vector2f,sf::Vector2f);
sf::Vector2f transferPixelToCords(sf::Vector2f);

  //  std::vector<std::unique_ptr<GameObj>> m_vec_obj;
    std::map<std::pair<unsigned int,unsigned int> , std::unique_ptr<GameObj>>m_vec_obj;
private:
    std::vector<std::vector<int>> m_map;
};
