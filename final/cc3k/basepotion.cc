#include "basepotion.h"

BasePotion::BasePotion(int x, int y) {
    this->x = x;
    this->y = y;
    this->val = 0;
    this->pt = PotionType::NewPotion;
}

/*int BasePotion::getX() {
    return x;
}

int BasePotion::getY() {
    return y;
}

int BasePotion::getValue() {
    return val;
}

PotionType BasePotion::getPT() {
    return pt;
}

Player* BasePotion::getPlayer() {
    return p;
}

void BasePotion::updateValue(int newVal) {
    this->val = newVal;
}

void BasePotion::updatePT(PotionType newPT) {
    this->pt = newPT;
}*/

void BasePotion::enhance(Player* pl) {}

BasePotion::~BasePotion() {
}

