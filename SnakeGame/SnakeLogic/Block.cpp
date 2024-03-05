#include <iostream>
#include "Vector.h"
#include "Block.h"


Vector* Block::getPos() const {
    return *&_pos;
}

Vector* Block::getDir() const {
    return *&_dir;
}

Vector* Block::index(int i) {
    if (i == 0)
        return *&_pos;
    if (_next)
        return _next->index(i - 1);
    throw std::exception("Blad w indeksie MOVEMENT");
}

Block::Block() {
    _pos->update(0, 0);
    _dir->update(0, 0);
}

Block::Block(int x, int y) {
    _pos->update(x, y);
}

Block::Block(int x, int y, int xd, int yd) {
    _pos->update(x, y);
    _dir->update(xd, yd);
}

void Block::Move() {
    if (_next) {
        _next->updateDir(_pos->x - _next->_pos->x, _pos->y - _next->_pos->y);
        _next->Move();
    }
    _pos->x += _dir->x;
    _pos->y += _dir->y;

}

void Block::updateDir(int x, int y) {
    _dir->x = x;
    _dir->y = y;
}

void Block::print() {
    std::cout << "Pozycja: " << _pos->x << ", " << _pos->y << std::endl;
    std::cout << "Kierunek: " << _dir->x << ", " << _dir->y << std::endl;
}

Block::~Block() {
    delete _pos;
    delete _dir;
    delete _next;
}

void Block::Add() {
    if (_next)
        _next->Add();
    else
        _next = new Block(_pos->x - _dir->x, _pos->y - _dir->y, _dir->x, _dir->y);
}