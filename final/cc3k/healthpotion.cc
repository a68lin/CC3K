#include "healthpotion.h"

HealthPotion::HealthPotion(Potion* potion, int val) : Decorator{potion} {
    this->pt = PotionType::HealthPotion;
    this->val = val;
}


void HealthPotion::enhance(Player* player) {
    potion->enhance(player);
    int hlt = player->getHp();
    int newhlt = hlt + (this->val);
    if (newhlt < 0) {
        newhlt = 0;
    } 
    if (player->getRace() == PlayerType::Human) {
        if (newhlt > 140) {
            newhlt = 140;
        }
    } else if (player->getRace() == PlayerType::Dwarf) {
        if (newhlt > 100) {
            newhlt = 100;
        }
    } else if (player->getRace() == PlayerType::Elves) {
        if (newhlt > 140) {
            newhlt = 140;
        }
    } else {
        if (newhlt > 180) {
            newhlt = 180;
        }
    }
    player->enhanceHealth(newhlt);
}



