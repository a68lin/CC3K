#include "defencepotion.h"

DefencePotion::DefencePotion(Potion* potion, int val) : Decorator{potion} {
    this->pt = PotionType::DefencePotion;
    this->val = val;
}


void DefencePotion::enhance(Player* player) { 
    potion->enhance(player);
    int def = (player)->getDefence();
    int newDef = def + (this->val);
    if (newDef < 0) {
        newDef = 0;
    } 
    player->enhanceDefence(newDef); //新的defence
}
