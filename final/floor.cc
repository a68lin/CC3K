bool floor::ifdoor(int x, int y) {
    if ((x == 4 && y = 29) || (x == 4 && y = 38) || (x == 7 && y = 43) || (x == 7 && y = 13) || (x == 9 && y = 43) ||
    (x == 11 && y = 60) || (x == 14 && y = 13) || (x == 13 && y = 43) || (x == 13 && y = 69) || (x == 15 && y = 69) ||
    (x == 18 && y = 43) || (x == 20 && y = 36) || (x == 20 && y = 25)) {
        return true;
    }
    reuturn false;
}

char floor::symbol(charType character) {
    if (character == charType::Werewolf) {
        return 'W';
    }
    if (character == charType::Vampire) {
        return 'V';
    }
    if (character == charType::Goblin) {
        return 'G';
    }
    if (character == charType::Merchant) {
        return 'M';
    }
    if (character == charType::Phoenix) {
        return 'X';
    }
    if (character == charType::Troll) {
        return 'T';
    }
    if (character == charType::Dragon) {
        return 'D';
    }
}

int floor::playerChamber() {
    int chamber_num = -1;
    for (int i = 0; i < 5; i++) {
        if (chambers[i]->getifplayer() == true) {
            return i;
        }
    }
}

void floor::attack(int x, int y) {
    int enemy_x, enemy_y;
    int chamber_num;
    chamber_num = playerChamber();
    if (chamber_num == -1) return;
    int player_x = chamber[chamber_num]->getplayer()->getX();
    int player_y = chamber[chamber_num]->getplayer()->getY();
    enemy_x = player_x + x;
    enemy_y = player_y + y;
    vector<enemy*> enemies = chamber[chamnber_num]->getenemies();
    for (auto it: enemies) {
        if (it->getX() == enemy_x && it->getY() == enemy_y) {
            chamber[chamber_num]->getplayer()->attackEnemy(it);
            if (*it->getHealth() != 0) {
                attackby(it);
            } else {
                map[it->getY()][it->getX()] = '.';
                int old_amount = chamber[chamber_num]->getplayer()->getGold();
                int add = it->getGold();
                chamber[chamber_num]->getplayer()->setGold(add + old_amount);
                enemies.erase(it);
            }
        }
    }
    if (chamber[chamber_num]->getplayer()->getHealth() == 0) map[player_y][player_x];
}

void floor::move(int x, int y) {
    int chamber_num;
    chamber_num = playerChamber();
    if (chamber_num == -1) {
        vector<vector<int> passway = passways->getpassway();
        int old_x = passways->getplayer()->getX();
        int old_y = passways->getplayer()->getY();
        int new_x = old_x + x;
        int new_y = old_y + y;
        for (auto it; passway) {
            if (it[0] == new_x && it[1] == new_y) {
                if (ifdoor(old_y, old)_x) {
                    map[old_y][old_x] = '+';
                } else {
                    map[old_y][old_x] = '#'
                }
                map[new_x][new_y] = '@';
                passways->getplayer()->setX(new_x);
                passways->getplayer()->setY(new_y);
            }
        }
    } else {
        int old_x = chamber[chamber_num]->getplayer()->getX();
        int old_y = chamber[chamber_num]->getplayer()->getY();
        int new_x = old_x + x;
        int new_y = old_y + y;
        char item = map[new_y][new_x];
        if (item != '.') {
            if (item == '+') {
                passways->setplayer(passways->getplayer());
                chamber[chamber_num]->setplayer(nullptr);
                passways->getplayer()->setX(new_x);
                passways->getplayer()->setY(new_y);
                map[old_x][old_y] = '.';
                map[new_x][new_y] = '@';
            } else if (item == 'G' || item == 'B') {
                vector<treasure*> goldPiles = chamber[chamber_num]->getTreasure();
                for (auto it: gold) {
                    if (Dragonhorde* dh = dynamic_cast<Dragonhorde*> it) {
                        if (dh->getStatue()) continue;
                    }
                    if (it->getX() == new_x && it->getY() == new_y) {
                        if (item == 'B') {
                            chamber[chamber_num]->getplayer()->setifBarrier(true);
                        } else {
                            int old_amount = chamber[chamber_num]->getplayer()->getGold();
                            int add = it->getAmount();
                             chamber[chamber_num]->getplayer()->setGold(add + old_amount);
                        }
                        map[old_x][old_y] = '.';
                        map[new_x][new_y] = '@';
                        goldPiles.erase(it);
                        chamber[chamber_num]->getplayer()->setX(new_x);
                        chamber[chamber_num]->getplayer()->setY(new_y);
                        break;
                    }
                }
            } else if (item == 'P') {
                chamber[chamber_num]->getplayer()
            }
        } else {
            map[old_x][old_y] = '.';
            map[new_x][new_y] = '@';
            chamber[chamber_num]->getplayer()->setX(new_x);
            chamber[chamber_num]->getplayer()->setY(new_y);
        }
    }
}

void floor::refresh() {
    for (int i = 0; i < 78; i++) {
        for (int j = 0; j < 24; j++) {
            vector<int> posn{i , j};
            for (int k = 0; k < 4; k++) {
                vector<enemies> enemies = chambers[k]->getEnemies();
                for (auto it: enemies) {
                    while(true) {
                        int old_x = it->getX();
                        int old_y = it->getY();
                        if (it->getRace() == CharType::Dragon) {
                          dragon* d = static_cast<dragon*>(enemies[0]);
                          d->dragonmove();
                      } else {
                          it->move();
                       }
                       if (map[it->getY()][it->getX()] == '.') {
                        map[it->getY()][it->getX()] = symbol(it->getRace());
                        map[old_y][old_x] = '.'; 
                        break;
                       }
                       it->setX(old_x);
                       it->setY(old_y);
                    }
                }
            }
        }
    }
}

void floor::print() {
    for (auto row: map) {
        for (auto column; row) {
            cout << column;
        }
        cout << endl;
    }
}