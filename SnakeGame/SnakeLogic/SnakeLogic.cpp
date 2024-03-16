#include <iostream>
#include <string>
#include "Snake.h"
#include "Block.h"
#include "Vector.h"
#include "Point.h"
#include <random>

using namespace std;

#define SNAKE_LENGTH 8
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
void DrawScreen(Snake* snake, Point point);
void direction(int a0, int a1, Vector*& dir);
void AStarXDAlg(Snake*& snake, Point point);

const Vector RIGHT = Vector(1, 0);
const Vector LEFT = Vector(-1, 0);
const Vector DOWN = Vector(0, 1);
const Vector UP = Vector(0, -1);

int main() {
    Snake* ptrSnake = new Snake(new Block(5, 5, 1, 0));
    ptrSnake->Add(SNAKE_LENGTH);

    srand((unsigned) time(NULL));

    Point point = Point(rand() % 40, rand() % 20);

    while (1) {
        if (GetKeyState('W') & 0x8000)
        {
            direction(500, 0, ptrSnake->head->dir);
        }

        if (GetKeyState('A') & 0x8000)
        {
            direction(1023, 500, ptrSnake->head->dir);
        }
        
        if (GetKeyState('S') & 0x8000)
        {
            direction(500, 1023, ptrSnake->head->dir);
        }
        
        if (GetKeyState('D') & 0x8000)
        {
            direction(0, 500, ptrSnake->head->dir);
        }

        AStarXDAlg(ptrSnake, point);

        ptrSnake->Move();

        if (ptrSnake->head->pos->x == point.pos->x && ptrSnake->head->pos->y == point.pos->y) {
            ptrSnake->Add();
            int x = rand() % 40;
            int y = rand() % 20;
            while (IsSnakePos(x, y, ptrSnake)) {
                x = rand() % 40;
                y = rand() % 20;
            }
            point.UpdatePos(x, y);
        }

        
        if (ptrSnake->ColisonCheck()) {
            goto GameEnd;
        }

        if (ptrSnake->head->pos->x > 40 or ptrSnake->head->pos->x < 0 or ptrSnake->head->pos->y > 20 or ptrSnake->head->pos->y < 0) {
            goto GameEnd;
            break;
        }
        
        DrawScreen(ptrSnake, point);
        Sleep(TIME_DELAY);
    }

    GameEnd:
        std::cout << "\nGame over!\nPoints scored: " << ptrSnake->Lenght() - SNAKE_LENGTH - 1 << "\n";

    delete ptrSnake;
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

void DrawScreen(Snake* ptrSnake, Point point) {
    system("CLS");
    string str = "||||||||||||||||||||||||||||||||||||||||||\n";
    for (unsigned char i = 0; i < 20; i++)
    {
        str += ("|");
        for (unsigned char j = 0; j < 40; j++)
        {
            if (IsSnakePos(j, i, ptrSnake)) {
                str += ("#");
            }
            else if (point.pos->x == j && point.pos->y == i) {
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
        dir->update(RIGHT); // right
    }
    else if (a0 > 1000) {
        dir->update(LEFT); // left
    }
    else if (a1 > 1000) {
        dir->update(DOWN); // down
    }
    else if (a1 < 15) {
        dir->update(UP); // up
    }
}

double CalculateDistance(Vector pos1, Point pos2) {
    return sqrt(pow(pos1.x - pos2.pos->x, 2) + pow(pos1.y - pos2.pos->x, 2));
}

Vector PredictPos(Vector pos, Vector dir) {
    return Vector(pos.x + dir.x, pos.y + dir.y);
}

void AStarXDAlg(Snake*& snake, Point point) {
    Vector pos = Vector(snake->head->pos->x, snake->head->pos->y);
    double left = CalculateDistance(PredictPos(pos, LEFT), point);
    double down = CalculateDistance(PredictPos(pos, DOWN), point);
    double right = CalculateDistance(PredictPos(pos, RIGHT), point);
    double up = CalculateDistance(PredictPos(pos, UP), point);
    
    cout << left << down << right << up;

    if (min(min(left, down), min(right, up)) == left) {
        snake->head->updateDir(LEFT);
    }
    if (min(min(left, down), min(right, up)) == down) {
        snake->head->updateDir(DOWN);
    }
    if (min(min(left, down), min(right, up)) == right) {
        snake->head->updateDir(RIGHT);
    }
    if (min(min(left, down), min(right, up)) == up) {
        snake->head->updateDir(UP);
    }
}
