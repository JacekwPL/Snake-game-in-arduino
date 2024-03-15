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

enum Vector::Direction {
    left = 1,
    up = 2,
    right = 4,
    down = 8
};

void Vector::update(Vector::Direction dir) {
    if (dir == Vector::Direction::up) {
        x = 0;
        y = -1;
    }
    if (dir == Vector::Direction::down) {
        x = 0;
        y = 1;
    }
    if (dir == Vector::Direction::up) {
        x = 0;
        y = -1;
    }
    if (dir == Vector::Direction::up) {
        x = 0;
        y = -1;
    }


}
