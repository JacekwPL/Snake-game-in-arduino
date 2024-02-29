#pragma once

class Vector {
public:
    int x, y;

    Vector(int xd, int yd);
    Vector();

    void update(int xd, int yd);
};