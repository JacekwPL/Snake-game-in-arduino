#include <iostream>
#include <time.h>

using namespace std;

#ifdef _WIN32
#include <windows.h>

void sleep(unsigned milliseconds)
{
    Sleep(milliseconds);
}
#else
#include <unistd.h>

void sleep(unsigned milliseconds)
{
    usleep(milliseconds * 1000); // takes microseconds
}
#endif

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

    void print() const {
        cout << x << " " << y << endl;
    }
    ~Vector() = default;
};

class Movement {
private:
    Vector* pos = new Vector();
    Vector* dir = new Vector();
    Movement* next = nullptr;
public:
    Vector* getPos() {
        return *&pos;
    }

    Vector* getDir() {
        return *&dir;
    }

    Vector* index(int i) {
        if (i == 0)
            return *&pos;
        if (next)
            return next->index(i - 1);
        throw exception("Blad w indeksie MOVEMENT");
    }

    Movement() {
        pos->update(0, 0);
        dir->update(0, 0);
    }
    
    Movement(int x, int y) {
        pos->update(x, y);
    }

    Movement(int x, int y, int xd, int yd) {
        pos->update(x, y);
        dir->update(xd, yd);
    }

    void Move() {
        if (next) {
            next->updateDir(pos->x - next->pos->x, pos->y - next->pos->y);
            next->Move();
        }
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
        delete next;
    }

    void Add(Movement* ptrMovement) {
        if (next)
            next->Add(ptrMovement);
        else
            next = ptrMovement;
    }

};

class Snake {
    Movement* _head;
    int count = 0;
public:
    int Lenght() {
        return count;
    }

    Snake(Movement* head) {
        _head = head;
        count += 1;
    }
    
    void Move() {
        if (_head)
            _head->Move();
    }
    void MoveDir(int x, int y) {
        if (_head)
            _head->updateDir(x, y);
            _head->Move();
    }
    Vector* Index(int i) {
        if (_head)
            return _head->index(i);
        else
            throw exception("Blad w indeksie SNAKE");
    }
    void Add(Movement* ptrMovement) {
        if (_head) {
            _head->Add(ptrMovement);
        }
        else
            _head = ptrMovement;
        count++;
    }

    ~Snake() {
        delete _head;
    }
};

bool IsSnakePos(int x, int y, Snake* ptrSnake) {
    Vector* arr;
    for (unsigned char i = 0; i < ptrSnake->Lenght(); i++)
    {
        arr = ptrSnake->Index(i);
        if (arr->x == x && arr->y == y) { return true; }
    }
    return false;
}

void DrawScreen(Snake* ptr) {
    cout << "|||||||||||||||||||||||||||";
    for (unsigned char i = 0; i < 10; i++)
    {
        for (unsigned char j = 0; j < 10; j++)
        {
            if (IsSnakePos(j, i, ptr)) {
                cout << "#";
            }
            else
                cout << " ";
        }
        cout << endl;
    }
}



int main() {
    Movement* ptrStart0 = new Movement(5, 5, 1, 0);
    Movement* ptrStart1 = new Movement(5, 4);
    Movement* ptrStart2 = new Movement(5, 3);
    Snake* ptrSnake = new Snake(ptrStart0);

    ptrSnake->Add(ptrStart1);
    ptrSnake->Add(ptrStart2);
    Sleep(1000);
    Sleep(1000);

    
    DrawScreen(ptrSnake);
    ptrSnake->Move();
    Sleep(1000);
    system("CLS");
    
    DrawScreen(ptrSnake);
    ptrSnake->MoveDir(0, -1);
    ptrSnake->Move();
    Sleep(1000);
    system("CLS");

    DrawScreen(ptrSnake);
    ptrSnake->Move();
    Sleep(1000);
    system("CLS");

    DrawScreen(ptrSnake);


    delete ptrStart0;
    delete ptrStart1;
    delete ptrStart2;
    delete ptrSnake;
    return 0;
}


