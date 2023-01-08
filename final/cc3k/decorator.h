#ifndef __DECORATOR_H__
#define __DECORATOR_H__
#include "potion.h"

class Decorator : public Potion {
protected:
    Potion* potion;
public:
    Decorator(Potion*);
    virtual void enhance(Player*);
    ~Decorator() = 0;
};
#endif
