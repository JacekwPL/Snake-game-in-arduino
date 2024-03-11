#include <Arduino.h>
#include "Snake.h"
#include "Block.h"
#include "Vector.h"
#include "Point.h"

const int SNAKE_LENGTH = 4;
const int TIME_DELAY = 300; //ms
const int YMAX = 20;
const int XMAX = 40;
const int SENSITIVITY = 50;

bool PointColision(Snake*, Point*);
bool IsSnakePos(int, int, Snake*);
void EndGame();
void direction(int a0, int a1, Vector*& dir);
bool IsEnd(Snake*);
void printPos(Snake*, Point*);

long long time = 0;

Snake* ptrSnake = new Snake(new Block(5, 5, 1, 0));
Point* ptrPoint = new Point(8, 5);
Vector* dir = new Vector();


void setup() {
  ptrSnake->Add(SNAKE_LENGTH);
  Serial.begin(9600);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

}

void loop() {
  if (PointColision(ptrSnake, ptrPoint)) {
    ptrSnake->Add();
    int x = rand() % XMAX;
    int y = rand() % YMAX;
    while (IsSnakePos(x, y, ptrSnake)) {
      x = rand() % XMAX;
      y = rand() % YMAX;

    }
    ptrPoint->UpdatePos(x, y);
  }

  if (ptrSnake->ColisonCheck() or IsEnd(ptrSnake)) {
    EndGame();
  }

  direction(analogRead(A0), analogRead(A1), ptrSnake->head->dir);

  if (time < millis()) {
    time += TIME_DELAY;
    ptrSnake->Move();
    printPos(ptrSnake, ptrPoint);
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
  ptrSnake->~Snake();

  ptrSnake = new Snake(new Block(5, 5, 1, 0));

  ptrSnake->Add(SNAKE_LENGTH);
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
  if (a1 < SENSITIVITY) {
    dir->update(1, 0);
  }
  else if (a0 > 1023-SENSITIVITY) {
    dir->update(0, 1);

  }
  else if (a1 > 1023-SENSITIVITY) {
    dir->update(-1, 0);

  }
  else if (a0 < SENSITIVITY) {
    dir->update(0, -1);
  }
}

void printPos(Snake* snake, Point* point) { 
  Block* head = snake->head;
  Vector* pnt = point->pos;
  if (pnt->x < 10) {
    Serial.print("0");
  }
  Serial.print(pnt->x);
  
  if (pnt->y < 10) {
    Serial.print("0");
  }
  Serial.print(pnt->y);
  
  while (head) {
    Vector* pos = head->pos;
    Serial.print("+");
   
    if (pos->x < 10) {
      Serial.print("0");
    }
    Serial.print(pos->x);
    
    if (pos->y < 10) {
      Serial.print("0");
    }
    Serial.print(pos->y);
   
    head = head->next;
  }
  Serial.print('\n');
}
