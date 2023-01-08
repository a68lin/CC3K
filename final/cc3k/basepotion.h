#ifndef __BASEPOTION_H__
#define __BASEPOTION_H__
#include "potion.h"
class BasePotion : public Potion{
public:
    BasePotion(int x, int y);
    /*int getX();
    int getY();
    int getValue();
    Player* getPlayer();
    PotionType getPT();
    void updateValue(int);
    void updatePT(PotionType);*/
    void enhance(Player*);
    ~BasePotion();
};
#endif



