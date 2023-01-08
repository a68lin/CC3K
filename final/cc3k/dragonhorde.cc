#include "dragonhorde.h"

DragonHorde::DragonHorde(int x, int y, int amount, bool ig, bool ib) : 
    x{x}, y{y}, amount{amount}, isGuarded{ig}, ifBarrier{ib} {}

DragonHorde::~DragonHorde() {}

DragonHorde::getStatue() {
    return isGuarded;
}

DragonHorde::getBarrier() {
    return ifBarrier;
}
