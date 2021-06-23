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
	void fillMap(const std::string &);
	void fillObjectMap(const std::string &);
	Floor& operator()(unsigned int, unsigned int)const;
    void UpdateAnimation(const float time);
    int getFloorScore(int x,int y)const;
	std::map<std::pair<float, float >, ptr>& getObjData() { return m_vec_obj; }
	void addObjects(float x, float y, PlayerOnline* obj);;
	void updateObjects(float x, float y, float z, float w);

private:

	std::map<std::pair<float, float >, ptr> m_vec_obj;
	std::vector<std::vector<std::unique_ptr<Floor>>> m_map;

};
