#include "Block.h"
#include "Snake.h"
#include <iostream>
#include <string>

using namespace std;

class Snake {
    Block* _head;
    int count = 0;
public:
    int Lenght() {
        return count;
    }

    Snake(Block* head) {
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
            _head = new Block(0, 0, 1, 0);
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
