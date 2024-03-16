#include <iostream>
#include "Vector.h"
#include "Block.h"


Vector* Block::getPos() const {
    return *&pos;
}

Vector* Block::getDir() const {
    return *&dir;
}

Vector* Block::index(int i) const {
    if (i == 0)
        return *&pos;
    if (_next)
        return _next->index(i - 1);
    throw std::exception("Blad w indeksie MOVEMENT");
}

Block::Block() {
    pos->update(0, 0);
    dir->update(0, 0);
}

Block::Block(int x, int y) {
    pos->update(x, y);
}

Block::Block(int x, int y, int xd, int yd) {
    pos->update(x, y);
    dir->update(xd, yd);
}

void Block::Move() {
    if (_next) {
        _next->updateDir(pos->x - _next->pos->x, pos->y - _next->pos->y);
        _next->Move();
    }
    pos->x += dir->x;
    pos->y += dir->y;

}

void Block::updateDir(int x, int y) {
    dir->x = x;
    dir->y = y;
}

void Block::updateDir(Vector pos) {
    dir->x = pos.x;
    dir->y = pos.y;
}

void Block::print() {
    std::cout << "Pozycja: " << pos->x << ", " << pos->y << std::endl;
    std::cout << "Kierunek: " << dir->x << ", " << dir->y << std::endl;
}

Block::~Block() {
    delete pos;
    delete dir;
    delete _next;
}

void Block::Add() {
    if (_next)
        _next->Add();
    else
        _next = new Block(pos->x - dir->x, pos->y - dir->y, dir->x, dir->y);
}