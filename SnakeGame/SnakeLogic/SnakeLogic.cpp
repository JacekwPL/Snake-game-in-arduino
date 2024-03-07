#include <iostream>
#include <string>
#include "Snake.h"
#include "Block.h"
#include "Vector.h"
#include "Point.h"
#include <random>

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

void DrawScreen(Snake* snake, Point* point) {
    system("CLS");
    string str = "||||||||||||||||||||||||||||||||||||||||||\n";
    for (unsigned char i = 0; i < 20; i++)
    {
        str+=("|");
        for (unsigned char j = 0; j < 40; j++)
        {
            if (IsSnakePos(j, i, snake)) {
                str += ("#");
            }
            else if (point->pos->x == j && point->pos->y == i) {
                str += ("+");
            }
            else
                str+=(" ");
        }
        str += ("|");
        str += ("\n");
    }
    str += ("||||||||||||||||||||||||||||||||||||||||||");
    cout << str;
}

int main() {
    Snake* ptrSnake = new Snake(new Block(5, 5, 1, 0));
    ptrSnake->Add(4);
    bool DidMove;

    srand((unsigned) time(NULL));

    Point* ptrPoint = new Point(8, 5);

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

        if (ptrSnake->head->pos->x == ptrPoint->pos->x &&
            ptrSnake->head->pos->y == ptrPoint->pos->y) {
            ptrSnake->Add();
            ptrPoint->UpdatePos(rand() % 30, rand() % 10);
        }

        DrawScreen(ptrSnake, ptrPoint);
        if (ptrSnake->ColisonCheck()) {
            std::cout << "Game over!\n";
            break;
        }

        if ((ptrSnake->head->pos->x > 40 or ptrSnake->head->pos->x < 0) or ((ptrSnake->head->pos->y > 20 or ptrSnake->head->pos->y < 0))) {
            std::cout << "Game over!\n";
            break;
        }
        

        Sleep(100);
    }


    delete ptrSnake;
    delete ptrPoint;
    return 0;
}


