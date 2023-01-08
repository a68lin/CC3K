#include "attackpotion.h"

AttackPotion::AttackPotion(Potion* potion, int val) : Decorator{potion} {
    this->pt = PotionType::AttackPotion;
    this->val = val;
}


void AttackPotion::enhance(Player* player) {
    potion->enhance(player);
    int att = player->getAttack();
    int newAtt = att + (this->val);
    if (newAtt < 0) {
        newAtt = 0;
    }
    player->enhanceAttack(newAtt);
}


