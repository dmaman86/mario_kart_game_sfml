#pragma once
#include "Object.h"

/*
	Floor 
	Holds : friction(Brick,Sand,Asphalt) 
		and position(score) on the map by the floor
*/
class Floor : public Object {
public: Floor(const int score) :Object::Object(),m_score(score) {};
	 const int getScore()const{return m_score;}
protected: 
	int m_score;
};

//================ Floor Brick : Drive you back ===========
class FloorBrick : public Floor {
public: 
	FloorBrick(const int score):Floor::Floor(score) {};
};

//================ Floor Sand : slows down ================
class FloorSand : public Floor {
public: 
	FloorSand(const int score) :Floor::Floor(score) {};
};

//================ Floor Asphalt : Normal road ============
class FloorAsphalt : public Floor {
public: 
	FloorAsphalt(const int score) :Floor::Floor(score) {};
};