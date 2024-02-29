#include <iostream>
#include "Vector.h"

using namespace std;

class Block {
private:
    Vector* _pos = new Vector();
    Vector* _dir = new Vector();
    Block* _next = nullptr;
public:
    Vector* getPos() {
        return *&_pos;
    }

    Vector* getDir() {
        return *&_dir;
    }

    Vector* index(int i) {
        if (i == 0)
            return *&_pos;
        if (_next)
            return _next->index(i - 1);
        throw exception("Blad w indeksie MOVEMENT");
    }

    Block() {
        _pos->update(0, 0);
        _dir->update(0, 0);
    }

    Block(int x, int y) {
        _pos->update(x, y);
    }

    Block(int x, int y, int xd, int yd) {
        _pos->update(x, y);
        _dir->update(xd, yd);
    }

    void Move() {
        if (_next) {
            _next->updateDir(_pos->x - _next->_pos->x, _pos->y - _next->_pos->y);
            _next->Move();
        }
        _pos->x += _dir->x;
        _pos->y += _dir->y;

    }

    void updateDir(int x, int y) {
        _dir->x = x;
        _dir->y = y;
    }

    void print() {
        cout << "Pozycja: " << _pos->x << ", " << _pos->y << endl;
        cout << "Kierunek: " << _dir->x << ", " << _dir->y << endl;
    }

    ~Block() {
        delete _pos;
        delete _dir;
        delete _next;
    }

    void Add() {
        if (_next)
            _next->Add();
        else
            _next = new Block(_pos->x - _dir->x, _pos->y - _dir->y, _dir->x, _dir->y);
    }
};