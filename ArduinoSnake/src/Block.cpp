#include "Vector.h"
#include "Block.h"


Vector* Block::getPos() const {
    return *&pos;
}

Vector* Block::getDir() const {
    return *&_dir;
}

Vector* Block::index(int i) const {
    if (i == 0)
        return *&pos;
    if (_next)
        return _next->index(i - 1);
    
}

Block::Block() {
    pos->update(0, 0);
    _dir->update(0, 0);
}

Block::Block(int x, int y) {
    pos->update(x, y);
}

Block::Block(int x, int y, int xd, int yd) {
    pos->update(x, y);
    _dir->update(xd, yd);
}

void Block::Move() {
    if (_next) {
        _next->updateDir(pos->x - _next->pos->x, pos->y - _next->pos->y);
        _next->Move();
    }
    pos->x += _dir->x;
    pos->y += _dir->y;

}

void Block::updateDir(int x, int y) {
    _dir->x = x;
    _dir->y = y;
}



Block::~Block() {
    delete pos;
    delete _dir;
    delete _next;
}

void Block::Add() {
    if (_next)
        _next->Add();
    else
        _next = new Block(pos->x - _dir->x, pos->y - _dir->y, _dir->x, _dir->y);
}