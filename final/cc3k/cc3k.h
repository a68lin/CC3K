#include <iostream>
#include <filestream>
#include <vector>
#include "Floor.h"

class cc3k {
    Floor* board;
public:
    cc3k();
    void init(char);
    void reset();
    void usePotion(int, int);
    void attack(int, int);
    void move(int, int);
    void print();
    bool ifnextfloor(int, int);
    bool ifPotion(int, int);
};