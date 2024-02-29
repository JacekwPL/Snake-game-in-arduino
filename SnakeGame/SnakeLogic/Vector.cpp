#include "Vector.h"

class Vector {
public:
    int x, y;

    Vector(int xd, int yd) {
        x = xd;
        y = yd;
    }
    Vector() {
        x = 0;
        y = 0;
    }

    void update(int xd, int yd) {
        x = xd;
        y = yd;
    }
};
