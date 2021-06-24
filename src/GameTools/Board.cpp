#include "Board.h"
#include <fstream>
#include <cmath>
#include "Macros.h"
#include "Pipe.h"
#include "Banana.h"
#include "Mushroom.h"
#include "Pictures.h"
#include "PlayerOnline.h"
#include "Utilities.h"
#include "Ghost.h"
#include "Coin.h"

Board::Board()
{

}

//=============================================================================
void Board::fillMap(const std::string& str)
{
    std::string name = str.substr(0,str.find('.'));
	auto map_int = readFromFile<char>(name+".txt");
    auto score_map = readFromFile<int>(name + "_scores.txt");
    m_map.resize(map_int.size());

    for (size_t i = 0;i < map_int.size();i++)
    {
        for (size_t j = 0;j < map_int[i].size();j++)
        {
            switch (map_int[i][j]-48)
            {
                case (int)FloorType::Asphalt:
                    m_map[i].push_back(std::make_unique<FloorAsphalt>(score_map[i][j]));
                    break;
                case (int)FloorType::Brick:
                    m_map[i].push_back(std::make_unique<FloorBrick>(score_map[i][j]));
                    break;
                case (int)FloorType::Sand:
                    m_map[i].push_back(std::make_unique<FloorSand>(score_map[i][j]));
                    break;
                default:
                    m_map[i].push_back(std::make_unique<FloorBrick>(score_map[i][j]));
                    break;
            }
        }
    }

}
//=============================================================================

Floor& Board::operator()(unsigned int i, unsigned int j)const {
	if (i < m_map.size() && j < m_map[0].size())
		return *m_map[i][j].get();
	throw std::range_error("m_map cannot get " + std::to_string(i) + " or "  +std::to_string(j));
}

//=============================================================================

void Board::fillObjectMap(const std::string& str)
{
	std::string name = str.substr(0, str.find('.'));
	auto map_int = readFromFile<int>(name + "_objects.txt",17,3);

	for (size_t i = 0;i < map_int.size();i++)
	{
		switch (map_int[i][0])
		{
		    case (int)ObjectType::ObjPipe:
			    m_vec_obj[std::pair(map_int[i][1],
                                    map_int[i][2])] = std::make_unique<Pipe>(sf::Vector2f(0, 0));
			    break;
		    case (int)ObjectType::ObjGhost:
			    m_vec_obj[std::pair(map_int[i][1],
                                    map_int[i][2])] = std::make_unique<Ghost>(sf::Vector2f(0, 0));
			    break;
		    case (int)ObjectType::ObjBanana:
			    m_vec_obj[std::pair(map_int[i][1],
                                    map_int[i][2])] = std::make_unique<Banana>(sf::Vector2f(0, 0));
			    break;
		    case (int)ObjectType::ObjCoin:
			    m_vec_obj[std::pair(map_int[i][1],
                                    map_int[i][2])] = std::make_unique<Coin>(sf::Vector2f(0, 0));
			    break;
		    case (int)ObjectType::ObjMushroom:
			    m_vec_obj[std::pair(map_int[i][1],
                                    map_int[i][2])] = std::make_unique<Mushroom>(sf::Vector2f(0, 0));
			    break;
		    default:
			    break;
		}
	}
}

//=============================================================================
void Board::UpdateAnimation(const float time)
{
    for(auto & vec:m_vec_obj)
        vec.second->UpdateAnimation(time);
}

//=============================================================================
int Board::getFloorScore(int x, int y) const
{
    if (x < m_map.size() && y < m_map[0].size())
        return m_map[x][y]->getScore();
    throw std::range_error("m_map cannot get " + std::to_string(x) + " or " + std::to_string(y));
}

//=============================================================================
void Board::addObjects(float x, float y, PlayerOnline *obj)
{
    m_vec_obj[std::pair(x, y)] = std::make_shared
            <PlayerOnline>(*obj);
}

//=============================================================================
void Board::updateObjects(float x, float y, float z, float w)
{
    if (auto it = m_vec_obj.find(std::pair(x, y)); it != m_vec_obj.cend())
    {
        auto nodeHandler = m_vec_obj.extract(std::pair(x, y));
        nodeHandler.key() = std::pair(z, w);
        m_vec_obj.insert(std::move(nodeHandler));
    }
}

//=============================================================================
