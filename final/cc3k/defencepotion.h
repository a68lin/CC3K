#ifndef __DEFENCEPOTION_H__
#define __DEFENCEPOTION_H__
#include "decorator.h"
class DefencePotion : public Decorator {
public:
    DefencePotion(Potion*, int);
    void enhance(Player*);
};

#endif
