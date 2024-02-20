#pragma once
#include "Block.h"

class Snake {
    Movement* _head;
    int count = 0;
public:
    int Lenght();

    Snake(Movement* head);

    void Move();
    void MoveDir(int x, int y);
    Vector* Index(int i);
    void Add();

    void Add(int i);

    ~Snake();
};

