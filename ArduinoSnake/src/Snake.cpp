#include "Block.h"
#include "Snake.h"

int Snake::Lenght() const {
    return count;
}

Snake::Snake(Block* newhead) {
    head = newhead;
    count += 1;
}

void Snake::Move() {
    if (head)
        head->Move();
}

void Snake::MoveDir(int x, int y) {
    if (head) {
        Vector* dir = head->getDir();

        if (!(-x == dir->x and -y == dir->y)) {
        head->updateDir(x, y);
        head->Move();
        }
    }
}

Vector* Snake::Index(int i) {
    // returns position of snake block begins from head (0) to tail (i)
    if (head)
        return head->index(i);
}

void Snake::Add() {
    if (head) {
        head->Add();
    }
    else {
        head = new Block(0, 0, 1, 0);
    }
    count++;
}

void Snake::Add(int i) {
    for (int x = 0; x < i; x++) {
        this->Add();
    }
}

Snake::~Snake() {
    delete head;
}

bool Snake::ColisonCheck() {
    int x = head->pos->x;
    int y = head->pos->y;
    Vector* arr;

    for (unsigned char i = 1; i < count; i++)
    {
        arr = this->Index(i);
        if (arr->x == x && arr->y == y) { return true; }
    }
    return false;
}