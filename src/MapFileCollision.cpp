#include "MapFileCollision.h"
#include <fstream>
#include <cmath>
#include "Macros.h"
#include "Pipe.h"
#include "Pictures.h"
#include "PlayerOnline.h"
MapFileCollision::MapFileCollision() {

}

void MapFileCollision::fillMap(const std::string str) {
	std::vector<std::vector <int>> map_int;
	std::ifstream m_file(str);
	int input;
	if (!m_file.is_open())
		throw std::range_error("cannot open m_file");
	for (int i = 0; i < 128; ++i)
	{
		std::vector<int> row;
		for (int j = 0; j < 128; ++j)
		{
			input = m_file.get() - 48;

			row.push_back(input);
		}
		m_file.get();
		map_int.push_back(row);
	}
	m_file.close();
	this->fillMap(map_int);
}

Floor& MapFileCollision::operator()(unsigned int i, unsigned int j) {
	if (i < m_map.size() && j < m_map[0].size())
		return *m_map[i][j].get();
	throw std::range_error("m_map cannot get i or j");
	//return {};
}
//
//float MapFileCollision::calcLength(sf::Vector2f a, sf::Vector2f b) {
//	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
//}

sf::Vector2f MapFileCollision::transferPixelToCords(sf::Vector2f loc) {

	return sf::Vector2f(loc / 8.f);
}

void MapFileCollision::fillMap(const std::vector<std::vector<int>>& map_int)
{
	m_map.resize(map_int.size());

	for (size_t i = 0;i < map_int.size();i++)
	{
		//m_map[i].resize(map_int[i].size());
		for (size_t j = 0;j < map_int[i].size();j++)
		{
			switch (map_int[i][j])
			{
			case 0:
				m_map[i].push_back(std::make_unique<FloorAsphalt>());
				break;
			case 1:
				m_map[i].push_back(std::make_unique<FloorBrick>());
				break;
			case 2:
				m_map[i].push_back(std::make_unique<FloorSand>());
				break;
			default:
				break;
			}
		}
	}
}

void MapFileCollision::fillObjectMap(std::string) {
	//m_vec_obj[std::pair(85*8, 88*4)] = std::make_unique<Pipe>(sf::Vector2f(0.0, 0.0), sf::Vector2f(85 , 88 ));
	//m_vec_obj[std::pair(415.0, 675.0)] = std::make_unique<Pipe>(sf::Vector2f(0.0, 0.0), sf::Vector2f(85, 88));
	//m_vec_obj[std::pair(815.0, 675.0)] = std::make_unique<Pipe>(sf::Vector2f(0.0, 0.0), sf::Vector2f(85, 88));

   // m_vec_obj[std::pair(85 * 4,88*8)]  = std::make_unique<Pipe>(sf::Vector2f(0.0,0.0),sf::Vector2f(615,675));


	// works
	m_vec_obj[std::pair(615.0, 675.0)] = std::make_unique<Pipe>(sf::Vector2f(0.0, 0.0), sf::Vector2f(615.0 / 8, 675.0 / 8));
	m_vec_obj[std::pair(595.0, 475.0)] = std::make_unique<Pipe>(sf::Vector2f(0.0, 0.0), sf::Vector2f(595.0 / 8, 475.0 / 8));
	m_vec_obj[std::pair(215.0, 437.0)] = std::make_unique<Pipe>(sf::Vector2f(0.0, 0.0), sf::Vector2f(215.0 / 8, 437.0 / 8));

	//m_vec_obj[std::pair(575.0, 500.0)] = std::make_unique<Pipe>(sf::Vector2f(0.0, 0.0), sf::Vector2f(575.0 / 8, 500.0 / 8));
	//m_vec_obj[std::pair(600.0, 500.0)] = std::make_unique<Pipe>(sf::Vector2f(0.0, 0.0), sf::Vector2f(600.0 / 8, 500.0 / 8));
	//m_vec_obj[std::pair(625.0, 500.0)] = std::make_unique<Pipe>(sf::Vector2f(0.0, 0.0), sf::Vector2f(625.0 / 8, 500.0 / 8));

	//m_vec_obj[std::pair(250.0, 525.0)] = std::make_unique<Pipe>(sf::Vector2f(0.0, 0.0), sf::Vector2f(250.0 / 8, 525.0 / 8));
	//m_vec_obj[std::pair(250.0, 575.0)] = std::make_unique<Pipe>(sf::Vector2f(0.0, 0.0), sf::Vector2f(250.0 / 8, 575.0 / 8));

	//m_vec_obj[std::pair(250.0, 500.0)] = std::make_unique<PlayerOnline>(Pictures::instance().getTexture(Pictures::KoopaDriver), sf::Vector2f(0.0, 0.0), sf::Vector2f(250.0 / 8, 500.0 / 8));
	//m_vec_obj[std::pair(625.0, 500.0)] = std::make_unique<PlayerOnline>(Pictures::instance().getTexture(Pictures::LuigiDriver), sf::Vector2f(0.0, 0.0), sf::Vector2f(625.0 / 8, 500.0 / 8));
}
