#include <iostream>
#include <string>
#include "Snake.h"
#include "Block.h"
#include "Vector.h"
#include "Point.h"
#include <random>

using namespace std;

#define SNAKE_LENGTH 4
#define TIME_DELAY 300 //ms
#define YMAX 20;
#define XMAX 40;

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
    ptrSnake->Add(SNAKE_LENGTH);
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

        if (ptrSnake->head->pos->x == ptrPoint->pos->x && ptrSnake->head->pos->y == ptrPoint->pos->y) {
            ptrSnake->Add();
            int x = rand() % 40;
            int y = rand() % 20;
            while (IsSnakePos(x, y, ptrSnake)) {
                x = rand() % 40;
                y = rand() % 20;
            }
            ptrPoint->UpdatePos(x, y);
        }

        
        if (ptrSnake->ColisonCheck()) {
            goto GameEnd;
        }

        if (ptrSnake->head->pos->x > 40 or ptrSnake->head->pos->x < 0 or ptrSnake->head->pos->y > 20 or ptrSnake->head->pos->y < 0) {
            goto GameEnd;
            break;
        }
        
        DrawScreen(ptrSnake, ptrPoint);
        Sleep(TIME_DELAY);
    }

    GameEnd:
        std::cout << "\nGame over!\nPoints scored: " << ptrSnake->Lenght() - SNAKE_LENGTH - 1 << "\n";

    delete ptrSnake;
    delete ptrPoint;
    return 0;
}


