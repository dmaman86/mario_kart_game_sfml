#pragma once 
#include "Macros.h"

class Line {

public:
	Line() { _x = _y = _z = 0; }

	// cooridates from world to screen
	void convertingCoordinates(int camx, int camy, int camz)
	{
		_scale = CAMERA_DEPTH / _z - camz;
		_X = (1 + _scale * (_x - camx)) * WITDH / 2;
		_Y = (1 - _scale * (_y - camy)) * HIGHT / 2;
		_Z = _scale * ROADW * WITDH / 2;
	}
	void updateZ(int i ){
		_z = i * SEGMENT_LENGTH;
	}
	const float getX() { return _X; }
	const float getY() { return _Y; }
	const float getZ() { return _Z; }

private:
	float _x, _y, _z;// 3d center of line
	float _X, _Y, _Z;// screen coor
	float _scale;
};
