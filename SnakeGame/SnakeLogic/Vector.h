#pragma once

struct Vector {
public:
    enum Direction;
    int x, y;
    Vector(int xd, int yd);
    Vector();
    void update(int xd, int yd);

    void update(Direction dir);

};

