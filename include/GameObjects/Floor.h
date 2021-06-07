#pragma once
#include "Player.h"
#include "Object.h"
class Floor : public Object {
public: Floor() :Object::Object() {};
};

class FloorBrick : public Floor {
public: 
	FloorBrick():Floor::Floor() {}; 
};

class FloorSand : public Floor {
public: 
	FloorSand() :Floor::Floor() {}; 
};

class FloorAsphalt : public Floor {
public: 
	FloorAsphalt() :Floor::Floor() {};
};