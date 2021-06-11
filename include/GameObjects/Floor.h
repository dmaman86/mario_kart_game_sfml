#pragma once
#include "Player.h"
#include "Object.h"
class Floor : public Object {
public: Floor(int score) :Object::Object(),m_score(score) {};
    int getScore()const{return m_score;}
protected: int m_score;
};

class FloorBrick : public Floor {
public: 
	FloorBrick(int score):Floor::Floor(score) {};
};

class FloorSand : public Floor {
public: 
	FloorSand(int score) :Floor::Floor(score) {};
};

class FloorAsphalt : public Floor {
public: 
	FloorAsphalt(int score) :Floor::Floor(score) {};
};