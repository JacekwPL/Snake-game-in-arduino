#include <iostream>

using namespace std;

struct Vector{
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

    void print() const {
        cout << x << " " << y << endl;
    }
    ~Vector() = default;
};

class Movement {
private:

    Vector* pos = new Vector();
    Vector* dir = new Vector();

public:
    Vector* getPos() {
        return *&pos;
    }

    Vector* getDir() {
        return *&dir;
    }

    Movement() = default;

    Movement(int x, int y) {
        pos->update(x, y);
    }

    Movement(int x, int y, int xd, int yd) {
        pos->update(x, y);
        dir->update(xd, yd);
    }

    void move() {
        pos->x += dir->x;
        pos->y += dir->y;
    }

    void updateDir(int x, int y) {
        dir->x = x;
        dir->y = y;
    }

    void print() {
        cout << "Pozycja: " << pos->x << ", " << pos->y << endl;
        cout << "Kierunek: " << dir->x << ", " << dir->y << endl;
    }

    ~Movement() {
        delete pos;
        delete dir;
    }

};




int main() {
    auto start = new Movement(5, 5, 1, 0);
    auto start2 = new Movement(5, 5);

    start->print();
    start->move();
    start->print();

    delete start;
    delete start2;

    return 0;
}


