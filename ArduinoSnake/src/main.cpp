#include <Arduino.h>
#include "Snake.h"
#include "Block.h"
#include "Vector.h"
#include "Point.h"

const int SNAKE_LENGTH = 4;
const int TIME_DELAY = 300; //ms
const int YMAX = 20;
const int XMAX = 40;

bool PointColision(Snake*, Point*);
bool IsSnakePos(int, int, Snake*);
void EndGame();
void direction(int a0, int a1, Vector*& dir);
bool IsEnd(Snake*);

Snake* ptrSnake = new Snake(new Block(5, 5, 1, 0));
Point* ptrPoint = new Point(8, 5);
Vector* dir = new Vector();
bool DidMove = false;

void setup() {
  // ptrSnake->Add(SNAKE_LENGTH);
  Serial.begin(9600);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

}

void loop() {
  // if (PointColision(ptrSnake, ptrPoint)) {
  //   ptrSnake->Add();
  //   int x = rand() % XMAX;
  //   int y = rand() % YMAX;
  //   while (IsSnakePos(x, y, ptrSnake)) {
  //     x = rand() % XMAX;
  //     y = rand() % YMAX;

  //   }
  //   ptrPoint->UpdatePos(x, y);
  // }

  // if (ptrSnake->ColisonCheck() or IsEnd(ptrSnake)) {
  //   EndGame();
  // }

  Serial.print("X ");
  Serial.print(analogRead(A0));
  Serial.print(" Y ");
  Serial.print(analogRead(A1));
  Serial.print(" S ");
  Serial.println(analogRead(A2));
  delay(500);
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

bool IsEnd(Snake* Snake) {
  Vector* pos = Snake->head->pos;
  return  pos->x > XMAX or 
          pos->x < 0 or 
          pos->y > YMAX or 
          pos->y < 0;
}

bool PointColision(Snake* snake, Point* point) {
  return snake->head->pos->x == point->pos->x && snake->head->pos->y == point->pos->y;
}

void direction(int a0, int a1, Vector*& dir) {
  if (a0 < 15) {
    dir->update(1, 0);
  }
  else if (a0 > 1000) {
    dir->update(-1, 0);
  }
  else if (a1 > 1000) {
    dir->update(0, 1);
  }
  else if (a1 < 15) {
    dir->update(0, -1);
  }
}