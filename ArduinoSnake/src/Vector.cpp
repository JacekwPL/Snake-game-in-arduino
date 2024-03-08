#include "Vector.h"

Vector::Vector(int xd, int yd) {
    x = xd;
    y = yd;
}

Vector::Vector() {
    x = 0;
    y = 0;
}

void Vector::update(int xd, int yd) {
    x = xd;
    y = yd;
}