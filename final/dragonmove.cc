#include "enemyFactory.h"
#include "playerFactory.h"
#include <iostream>


int main() {
    enemyFactory EFA;
    playerFactory PFA;

    std::vector<player*> players;
    std::vector<enemy*> enemies;

    players.emplace_back(PFA.createHuman(1, 1));
    enemies.emplace_back(EFA.createDragon(5, 4, true, 5, 5));


    if (enemies[0]->getRace() == CharType::Dragon) {
        dragon* p = static_cast<dragon*>(enemies[0]);
    p->dragonmove();
    std::cout <<  enemies[0]->getX() << enemies[0]->getY() << std::endl;
    p->dragonmove();
    std::cout <<  enemies[0]->getX() << enemies[0]->getY() << std::endl;
    p->dragonmove();
    std::cout <<  enemies[0]->getX() << enemies[0]->getY() << std::endl;
    p->dragonmove();
    std::cout <<  enemies[0]->getX() << enemies[0]->getY() << std::endl;
    }
}