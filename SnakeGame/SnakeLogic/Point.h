#pragma once
#include "Vector.h"

class Point
{
public:
	Vector* pos = new Vector(0, 0);

	Point();
	Point(int, int);
	
	void UpdatePos(int, int);

};

