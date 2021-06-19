#pragma once
#include <string>
#include <vector>
#include <map>
#include "GameObj.h"
#include <algorithm>
#include "PlayerOnline.h"
#include "Floor.h"
typedef std::shared_ptr<GameObj> ptr;

class Board {
public:

	Board();
	void fillMap(const std::string);
	void fillObjectMap(const std::string);
	Floor& operator()(unsigned int, unsigned int);
	sf::Vector2f transferPixelToCords(sf::Vector2f);
    int getFloorScore(int x,int y){return m_map[x][y]->getScore();}
	std::map<std::pair<float, float >, ptr>& getObjData() { return m_vec_obj; }
	void addObjects(float x, float y, PlayerOnline* obj)
	{
		m_vec_obj[std::pair(x, y)] = std::make_shared
			<PlayerOnline>(*obj);
	};
	void updateObjects(float x, float y, float z, float w)
	{
		if (auto it = m_vec_obj.find(std::pair(x, y));it != m_vec_obj.cend()) {
			auto nodeHandler = m_vec_obj.extract(std::pair(x, y));
			nodeHandler.key() = std::pair(z, w);
			m_vec_obj.insert(std::move(nodeHandler));

		}
	}

private:

	std::map<std::pair<float, float >, ptr> m_vec_obj;
	void fillMap(const std::vector<std::vector<char>> &);
	std::vector<std::vector<std::unique_ptr<Floor>>> m_map;

}; // end Board
