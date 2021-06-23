#pragma once

/*
	Object: Base class of GameObj and Floor
	So that in a collision we can check 
	between them with the same base class
*/
class Object {

public:
	Object() {};
	virtual ~Object() = default;

private:

};//end Object