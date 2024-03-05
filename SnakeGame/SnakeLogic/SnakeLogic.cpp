#include <iostream>
#include <string>
#include "Snake.h"
#include "Block.h"
#include "Vector.h"

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
    Snake* ptrSnake = new Snake(new Block(5, 5, 1, 0));

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


