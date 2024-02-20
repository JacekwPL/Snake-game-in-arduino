#include <iostream>

using namespace std;

struct Vector {
public:
    int x, y;

    Vector(int xd, int yd) {
        x = xd;
        y = yd;
    }
    Vector() {
        x = 0;
        y = 0;
    }

    void update(int xd, int yd) {
        x = xd;
        y = yd;
    }
};

class Movement {
private:
    Vector* _pos = new Vector();
    Vector* _dir = new Vector();
    Movement* _next = nullptr;
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

    Movement() {
        _pos->update(0, 0);
        _dir->update(0, 0);
    }

    Movement(int x, int y) {
        _pos->update(x, y);
    }

    Movement(int x, int y, int xd, int yd) {
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

    ~Movement() {
        delete _pos;
        delete _dir;
        delete _next;
    }

    void Add() {
        if (_next)
            _next->Add();
        else
            _next = new Movement(_pos->x - _dir->x, _pos->y - _dir->y, _dir->x, _dir->y);
    }
};