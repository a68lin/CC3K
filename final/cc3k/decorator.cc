#include "decorator.h"

Decorator::Decorator(Potion* p) : 
    potion{p} {}

Decorator::~Decorator() {
    delete potion;
}


void Decorator::enhance(Player* pl) {}