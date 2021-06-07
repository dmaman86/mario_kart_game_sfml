#pragma once
#include <string>
#include <vector>
#include <map>
#include "GameObj.h"
#include <algorithm>
#include "PlayerOnline.h"
#include "Floor.h"

class MapFileCollision {
public:

	MapFileCollision();
	void fillMap(const std::string);
	void fillObjectMap(const std::string);
	Floor& operator()(unsigned int, unsigned int);
	//float calcLength(sf::Vector2f, sf::Vector2f);
	sf::Vector2f transferPixelToCords(sf::Vector2f);
	void addObjects(float x, float y, PlayerOnline* obj)
	{
		m_vec_obj[std::pair(x, y)] = std::make_unique
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
	//  std::vector<std::unique_ptr<GameObj>> m_vec_obj;
	std::map<std::pair<float, float >, std::unique_ptr<GameObj>> m_vec_obj;

private:

	void fillMap(const std::vector<std::vector<int>>&);
	std::vector<std::vector<std::unique_ptr<Floor>>> m_map;
};
