#pragma once
#include "Vector.h"


class Block {
private:
    Block* _next = nullptr;
public:
    Vector* dir = new Vector();

    Vector* pos = new Vector();
    Vector* getPos() const ;

    Vector* getDir() const ;

    Vector* index(int i) const ;

    Block();

    Block(int x, int y);

    Block(int x, int y, int xd, int yd);

    void Move();

    void updateDir(int x, int y);

    void print();
    void updateDir(Vector pos);
    ~Block();

    bool const operator==(Block other) const {
        return this->pos->x == other.pos->x && this->pos->y == other.pos->y;
    }

    bool const operator!=(Block other) const {
        throw std::exception("not implemented yet");
        return ((*this) == other);
    }

    void Add();
};
