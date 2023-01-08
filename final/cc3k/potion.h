#ifndef __POTION_H__
#define __POTION_H__
#include "myplayer.h"
enum class PotionType { NewPotion, HealthPotion, AttackPotion, DefencePotion };

class Potion {
protected:    
    int x;
    int y;
    int val;
    PotionType pt;
public:
    virtual void enhance(Player*) = 0;
    virtual ~Potion() = default;
};



#endif

