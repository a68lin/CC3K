#ifndef _FLOOR_H_
#define _FLOOR_H_
#include <vector>
#include "chamber.h"
#include "passway.h"
using namespace std;
class Floor{
    protected:
    vector<vector<char>> map;
    vector<Chamber*> chambers;
    Passways* passways;
    bool ifAttackMerchant;
    bool ifBarrierAppeared;
    bool ifCompassCarried;
    public:
    Floor(char);
    ~Floor();
    vector<int> randomPosn();
    void ifdoor(int x, int y);
    int playerChamber();
    void attack(int x, int y);
    void move(int x, int y);
    void refresh();
    void print();
};

#endif