#include <Arduino.h>
#include "Snake.h"
#include "Block.h"
#include "Vector.h"
#include "Point.h"

#define SNAKE_LENGTH 4
#define TIME_DELAY 300 //ms
#define YMAX 20;
#define XMAX 40;

bool IsSnakePos(int, int, Snake*);
void EndGame();

Snake* ptrSnake = new Snake(new Block(5, 5, 1, 0));
Point* ptrPoint = new Point(8, 5);
bool DidMove = false;


void setup() {
  ptrSnake->Add(SNAKE_LENGTH);
}

void loop() {
    
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
    EndGame();
  }

  if (ptrSnake->head->pos->x > 40 or ptrSnake->head->pos->x < 0 or ptrSnake->head->pos->y > 20 or ptrSnake->head->pos->y < 0) {
    EndGame();
  }


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


void EndGame() {
    delete ptrSnake;
    delete ptrPoint;
}
