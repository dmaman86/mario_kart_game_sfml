#pragma once
#include <string>
#include <vector>

class MapFileCollision {
public:

MapFileCollision();
void fillMap(const std::string);
int operator()(unsigned int,unsigned int);

private:
    std::vector<std::vector<int>> m_map;
};
