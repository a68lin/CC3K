#ifndef __TREASURE_H__
#define __TREASURE_H__
class Treasure {
    int x;
    int y;
    int amount;
public:
    Treasure(int, int, int);
    int getX();
    int getY();
    int getAmount();
    ~Treasure();
};



#endif
