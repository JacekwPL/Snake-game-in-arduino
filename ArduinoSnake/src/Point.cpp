#include "Point.h"

Point::Point()
	: pos(new Vector(0, 0))
{ }

Point::Point(int x, int y) 
	: pos(new Vector(x, y))
{ }

void Point::UpdatePos(int x, int y) {
	pos->update(x, y);
}