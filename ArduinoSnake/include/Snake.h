
#include "Block.h"
#include "Vector.h"

class Snake {
    int count = 0;

public:
    Block* head;
    int Lenght() const ;

    Snake(Block* head);

    void Move();
    
    void MoveDir(int x, int y);
    
    Vector* Index(int i);
    
    void Add();

    void Add(int i);

    bool ColisonCheck();
    
    ~Snake();
};


