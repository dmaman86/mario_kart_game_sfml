#include "MapFileCollision.h"
#include <fstream>

MapFileCollision::MapFileCollision() {

}

void MapFileCollision::fillMap(const std::string str) {
    std::ifstream m_file(str);
    if(!m_file.is_open())
        throw std::range_error("cannot open m_file");
    for (int i = 0; i < 128; ++i)
    {
        std::vector<int> row;
        for (int j = 0; j < 128; ++j)
        {
            row.push_back(m_file.get() - 48);
        }
        m_file.get();
        m_map.push_back(row);
    }
    m_file.close();
}

int MapFileCollision::operator()(unsigned int i, unsigned int j) {
    if(i < m_map.size() && j < m_map[0].size())
        return m_map[i][j];
    throw std::range_error("m_map cannot get i or j");
    return -1;
}
