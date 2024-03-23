#include "Block.h"
#include "Snake.h"
#include <iostream>
#include <string>


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
    else {
        std::exception("Head wasn't initialize!");
    }
}
Vector* Snake::Index(int i) {
    // returns position of snake block begins from head (0) to tail (i)
    if (head)
        return head->index(i);
    else
        throw std::exception("Blad w indeksie SNAKE");
}

Vector* Snake::retArray() {
    Vector* array = new Vector[count];
    for (int i = 0; i < count; i++)
    {
        array[i] = *Index(i);
    }
    return array;
}

void Snake::Add() {
    if (head) {
        head->Add();


    }
    else {
        std::cout << "WARNING, HEAD WASNT INITIALIZE" << std::endl;
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

int const Snake::ArrayLenght() const {
    return count;
}
