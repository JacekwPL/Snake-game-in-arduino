#pragma once
#include <iostream>

using namespace std;

struct Vector {
public:
    int x, y;

    Vector(int xd, int yd);
    Vector();

    void update(int xd, int yd);
};

class Movement {
private:
    Vector* _pos = new Vector();
    Vector* _dir = new Vector();
    Movement* _next = nullptr;
public:
    Vector* getPos();

    Vector* getDir();

    Vector* index(int i);

    Movement();

    Movement(int x, int y);

    Movement(int x, int y, int xd, int yd);

    void Move();

    void updateDir(int x, int y);

    void print();

    ~Movement();

    void Add();
};