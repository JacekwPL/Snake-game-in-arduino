#include <iostream>
#include <string>

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
    void Add() {
        if (_head) {
            _head->Add();
        }
        else {
            cout << "WARNING, HEAD WASNT INITIALIZE" << endl;
            _head = new Movement(0, 0, 1, 0);
        }
        count++;
    }

    void Add(int i) {
        for (int x = 0; x < i; x++) {
            this->Add();
        }
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
    system("CLS");
    string str = "|||||||||||||||||||||||||||\n";
    for (unsigned char i = 0; i < 20; i++)
    {
        str+=("|");
        for (unsigned char j = 0; j < 40; j++)
        {
            if (IsSnakePos(j, i, ptr)) {
                str += ("#");
            }
            else
                str+=(" ");
        }
        str += ("|");
        str += ("\n");
    }
    str += ("|||||||||||||||||||||||||||");
    cout << str;
}



int main() {
    Snake* ptrSnake = new Snake(new Movement(5, 5, 1, 0));

    ptrSnake->Add(40);
    bool DidMove;
    while (1) {
        DidMove = 0;
        if (GetKeyState('W') & 0x8000)
        {
            ptrSnake->MoveDir(0, -1);
            DidMove = 1;
        }

        if (GetKeyState('A') & 0x8000)
        {
            ptrSnake->MoveDir(-1, 0);
            DidMove = 1;
        }
        
        if (GetKeyState('S') & 0x8000)
        {
            ptrSnake->MoveDir(0, 1);
            DidMove = 1;
        }
        
        if (GetKeyState('D') & 0x8000)
        {
            ptrSnake->MoveDir(1, 0);
            DidMove = 1;
        }
        DrawScreen(ptrSnake);
        Sleep(500);
    }

    delete ptrSnake;
    return 0;
}


