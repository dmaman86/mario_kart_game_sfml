#pragma once
#include <string>
#include <vector>
#include <map>
#include "GameObj.h"
#include <algorithm>
#include "PlayerOnline.h"
#include "Floor.h"

/*
	Board:
	Holds the objects of the game and the entire floor
*/
class Board
{
public:
    typedef std::shared_ptr<GameObj> ptr;
public:
	//Constuctor
	Board() {};
	//Public Functions
	void fillMap(const std::string &);
	void fillObjectMap(const std::string &);
	Floor& operator()(unsigned int, unsigned int)const;
    void UpdateAnimation(const float time);
    int getFloorScore(int x,int y)const;
	std::map<std::pair<float, float >, ptr>& getObjData() { return m_vec_obj; }
	void addObjects(float x, float y, PlayerOnline* obj);;
	void updateObjects(float x, float y, float z, float w);

private:

	//private enum class 
	enum class FloorType
    {
        Asphalt,
        Brick,
        Sand
    };
	enum class ObjectType
    {
	    ObjPipe = 1,
	    ObjGhost,
	    ObjBanana,
	    ObjCoin,
	    ObjMushroom
    };

	//private members
	std::map<std::pair<float, float >, ptr> m_vec_obj;
	std::vector<std::vector<std::unique_ptr<Floor>>> m_map;

};//end Board
