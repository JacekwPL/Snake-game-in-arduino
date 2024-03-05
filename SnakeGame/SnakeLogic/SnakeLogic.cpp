﻿#include <iostream>
#include <string>
#include "Snake.h"
#include "Block.h"
#include "Vector.h"
#include "Point.h"

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



bool IsSnakePos(int x, int y, Snake* ptrSnake) {
    Vector* arr;
    for (unsigned char i = 0; i < ptrSnake->Lenght(); i++)
    {
        arr = ptrSnake->Index(i);
        if (arr->x == x && arr->y == y) { return true; }
    }
    return false;
}

void DrawScreen(Snake*& snake, Point*& point) {
    system("CLS");
    string str = "|||||||||||||||||||||||||||\n";
    for (unsigned char i = 0; i < 20; i++)
    {
        str+=("|");
        for (unsigned char j = 0; j < 40; j++)
        {
            if (IsSnakePos(j, i, snake)) {
                str += ("#");
            }
            else if (point->pos->x == j && point->pos->x == i) {
                str += ("+");
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
    Snake* ptrSnake = new Snake(new Block(5, 5, 1, 0));
    ptrSnake->Add(4);
    bool DidMove;

    Point* ptrPoint = new Point(0, 0);

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

        if (DidMove == 0)
            ptrSnake->Move();

        DrawScreen(ptrSnake, ptrPoint);
        Sleep(500);
    }

    delete ptrSnake;
    delete ptrPoint;
    return 0;
}


