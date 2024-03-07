#pragma once
#include "Vector.h"

class Point
{
public:
	Vector* pos = new Vector(0, 0);

	Point();
	Point(int x, int y);
	
	void UpdatePos(int x, int y);

};

