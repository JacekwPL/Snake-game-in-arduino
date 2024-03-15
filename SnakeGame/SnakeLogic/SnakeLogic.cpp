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

bool IsSnakePos(int x, int y, Snake* ptrSnake);
void DrawScreen(Snake* snake, Point* point);
void direction(int a0, int a1, Vector*& dir);
Vector* AStarXDAlg(Snake* snake, Point* point);



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
            direction(500, 0, ptrSnake->head->dir);
            DidMove = 1;
        }

        if (GetKeyState('A') & 0x8000)
        {
            direction(1023, 500, ptrSnake->head->dir);
            DidMove = 1;
        }
        
        if (GetKeyState('S') & 0x8000)
        {
            direction(500, 1023, ptrSnake->head->dir);
            DidMove = 1;
        }
        
        if (GetKeyState('D') & 0x8000)
        {
            direction(0, 500, ptrSnake->head->dir);
            DidMove = 1;
        }

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
        str += ("|");
        for (unsigned char j = 0; j < 40; j++)
        {
            if (IsSnakePos(j, i, snake)) {
                str += ("#");
            }
            else if (point->pos->x == j && point->pos->y == i) {
                str += ("+");
            }
            else
                str += (" ");
        }
        str += ("|");
        str += ("\n");
    }
    str += ("||||||||||||||||||||||||||||||||||||||||||");
    cout << str;
}

void direction(int a0, int a1, Vector*& dir) {
    if (a0 < 15) {
        dir->update(1, 0); // right
    }
    else if (a0 > 1000) {
        dir->update(-1, 0); // left
    }
    else if (a1 > 1000) {
        dir->update(0, 1); // down
    }
    else if (a1 < 15) {
        dir->update(0, -1); // up
    }
}

Vector* AStarXDAlg(Snake* snake, Point* point) {
    Vector* list = new Vector[3];
    


    delete[] list;
}
