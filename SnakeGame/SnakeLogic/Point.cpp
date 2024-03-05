#include "Point.h"

Point::Point() {
	pos->update(0, 0);
}

Point::Point(int x, int y) {
	pos->update(x, y);
}

void Point::UpdatePos(int x, int y) {
	pos->update(x, y);
}