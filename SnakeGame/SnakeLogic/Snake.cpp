#include "Block.h"
#include "Snake.h"
#include <iostream>
#include <string>


int Snake::Lenght() const {
    return count;
}

Snake::Snake(Block* head) {
    _head = head;
    count += 1;
}

void Snake::Move() {
    if (_head)
        _head->Move();
}
void Snake::MoveDir(int x, int y) {
    if (_head)
        _head->updateDir(x, y);
    _head->Move();
}
Vector* Snake::Index(int i) {
    if (_head)
        return _head->index(i);
    else
        throw std::exception("Blad w indeksie SNAKE");
}
void Snake::Add() {
    if (_head) {
        _head->Add();
    }
    else {
        std::cout << "WARNING, HEAD WASNT INITIALIZE" << std::endl;
        _head = new Block(0, 0, 1, 0);
    }
    count++;
}

void Snake::Add(int i) {
    for (int x = 0; x < i; x++) {
        this->Add();
    }
}

Snake::~Snake() {
    delete _head;
}

