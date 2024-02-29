#pragma once
#include "Block.h"
#include "Vector.h"

class Snake {
    Block* _head;
    int count = 0;
public:
    int Lenght();

    Snake(Block* head);

    void Move();
    void MoveDir(int x, int y);
    Vector* Index(int i);
    void Add();

    void Add(int i);

    ~Snake();
};

