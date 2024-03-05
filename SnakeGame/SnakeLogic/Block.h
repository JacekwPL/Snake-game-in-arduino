#pragma once
#include "Vector.h"

class Block {
private:
    Vector* _pos = new Vector();
    Vector* _dir = new Vector();
    Block* _next = nullptr;
public:
    Vector* getPos() const ;

    Vector* getDir() const ;

    Vector* index(int i);

    Block();

    Block(int x, int y);

    Block(int x, int y, int xd, int yd);

    void Move();

    void updateDir(int x, int y);

    void print();

    ~Block();

    void Add();
};
