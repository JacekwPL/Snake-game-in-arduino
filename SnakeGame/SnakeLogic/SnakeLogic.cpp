#include <iostream>
#include <random>
#include <string>
#include "Snake.h"
#include "Block.h"
#include "Vector.h"
#include "Point.h"

#define POW2(x) ((x)*(x))
#define min4(a, b, c, d) (min(min(a, b), min(c, d)))

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

const int TIME_DELAY = 100; //ms 
const char SNAKE_LENGTH = 8;
const char YMAX = 20;
const char XMAX = 40;

bool IsSnakePos(int x, int y, Snake* ptrSnake);
void DrawScreen(Snake* snake, Point point);
void direction(int a0, int a1, Vector*& dir);
void AStarXDAlg(Snake*& snake, Point &point);

const Vector VRIGHT = Vector(1, 0);
const Vector VLEFT = Vector(-1, 0);
const Vector VDOWN = Vector(0, 1);
const Vector VUP = Vector(0, -1);

int main() {

    auto t1 = Block(5, 4);
    auto t2 = Block(5, 4);
    auto t3 = Block(3, 4);

    std::cout << (t1 == t2) << std::endl;
    std::cout << (t1 == t3) << std::endl;
    std::cout << (t1 != t3) << std::endl;
    std::cout << "siema eniu";


    //Snake* ptrSnake = new Snake(new Block(5, 5, 1, 0));
    //ptrSnake->Add(SNAKE_LENGTH);

    //srand((unsigned) time(NULL));

    //Point point = Point(rand() % XMAX, rand() % YMAX);

    //while (1) {
    //    if (GetKeyState('W') & 0x8000)
    //    {
    //        direction(500, 0, ptrSnake->head->dir);
    //    }

    //    if (GetKeyState('A') & 0x8000)
    //    {
    //        direction(1023, 500, ptrSnake->head->dir);
    //    }
    //    
    //    if (GetKeyState('S') & 0x8000)
    //    {
    //        direction(500, 1023, ptrSnake->head->dir);
    //    }
    //    
    //    if (GetKeyState('D') & 0x8000)
    //    {
    //        direction(0, 500, ptrSnake->head->dir);
    //    }

    //    AStarXDAlg(ptrSnake, point);

    //    ptrSnake->Move();

    //    if (ptrSnake->head->pos->x == point.pos->x && ptrSnake->head->pos->y == point.pos->y) {
    //        ptrSnake->Add();
    //        int x = rand() % XMAX;
    //        int y = rand() % YMAX;
    //        while (IsSnakePos(x, y, ptrSnake)) {
    //            x = rand() % XMAX;
    //            y = rand() % YMAX;
    //        }
    //        point.UpdatePos(x, y);
    //    }

    //    
    //    if (ptrSnake->ColisonCheck()) {
    //        goto GameEnd;
    //    }

    //    if (ptrSnake->head->pos->x > XMAX or ptrSnake->head->pos->x < 0 or ptrSnake->head->pos->y > YMAX or ptrSnake->head->pos->y < 0) {
    //        goto GameEnd;
    //        break;
    //    }
    //    
    //    DrawScreen(ptrSnake, point);
    //    Sleep(TIME_DELAY);
    //}

    //GameEnd:
    //    std::cout << "\nGame over!\nPoints scored: " << ptrSnake->Lenght() - SNAKE_LENGTH - 1 << "\n";

    //delete ptrSnake;
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
    std::string str = "||||||||||||||||||||||||||||||||||||||||||\n";
    for (unsigned char i = 0; i < YMAX; i++)
    {
        str += ("|");
        for (unsigned char j = 0; j < XMAX; j++)
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
    std::cout << str;
}

void direction(int a0, int a1, Vector*& dir) {
    if (a0 < 15) {
        dir->update(VRIGHT); // right
    }
    else if (a0 > 1000) {
        dir->update(VLEFT); // left
    }
    else if (a1 > 1000) {
        dir->update(VDOWN); // down
    }
    else if (a1 < 15) {
        dir->update(VUP); // up
    }
}

void AStarXDAlg(Snake*& snake, Point& point) {
    Vector SnakePos = Vector(snake->head->pos->x, snake->head->pos->y);
    Vector PointPos = Vector(point.pos->x, point.pos->y);
    int up = POW2(SnakePos.x + VUP.x - PointPos.x) + POW2(SnakePos.y + VUP.y - PointPos.y);
    int down = POW2(SnakePos.x + VDOWN.x - PointPos.x) + POW2(SnakePos.y + VDOWN.y - PointPos.y);
    int left = POW2(SnakePos.x + VLEFT.x - PointPos.x) + POW2(SnakePos.y + VLEFT.y - PointPos.y);
    int right = POW2(SnakePos.x + VRIGHT.x - PointPos.x) + POW2(SnakePos.y + VRIGHT.y - PointPos.y);
    
    std::cout << left << " " << down << " " << right << " " << up;

    if (min4(left, down, right, up) == left) {
        snake->head->updateDir(VLEFT);
    }
    else if (min4(left, down, right, up) == right) {
        snake->head->updateDir(VRIGHT);
    }
    else if (min4(left, down, right, up) == up) {
        snake->head->updateDir(VUP);
    }
    else if (min4(left, down, right, up) == down) {
        snake->head->updateDir(VDOWN);
    }
}
