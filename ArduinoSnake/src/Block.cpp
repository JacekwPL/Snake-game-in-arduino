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
    if (next)
        return next->index(i - 1);
    
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
    if (next) {
        next->updateDir(pos->x - next->pos->x, pos->y - next->pos->y);
        next->Move();
    }
    pos->x += dir->x;
    pos->y += dir->y;

}

void Block::updateDir(int x, int y) {
    dir->x = x;
    dir->y = y;
}



Block::~Block() {
    delete pos;
    delete dir;
    delete next;
}

void Block::Add() {
    if (next)
        next->Add();
    else
        next = new Block(pos->x - dir->x, pos->y - dir->y, dir->x, dir->y);
}