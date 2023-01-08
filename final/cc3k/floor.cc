#include "floor.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
Floor::Floor(char race){
    //used to randomly generate chamber
    vector<int> v = {0,1,2,3,4};
    vector<bool> vplayer ={true, false, false, false, false};
    vector<bool> vcompass ={true, false, false, false, false};
    vector<bool> vstair ={true, false, false, false, false};
    vector<bool> vsuite ={true, false, false, false, false};
    //number of enemies in each chamber
    int numEne[5] = {0,0,0,0,0};
    int numPotion[5]= {0,0,0,0,0};
    int numGold[5] = {0,0,0,0,0,};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle( vplayer.begin(), vplayer.end(), rng );
    std::shuffle( vcompass.begin(), vcompass.end(), rng );
    std::shuffle( vstair.begin(), vstair.end(), rng );
    std::shuffle( vsuite.begin(), vsuite.end(), rng );
    for ( int i = 0; i < 10; i++ ) {
		//std::shuffle( v.begin(), v.end(), std::default_random_engine(seed) );
		std::shuffle( v.begin(), v.end(), rng );
		int addNum = v[0];
        //enemies + 1
        numPotion[addNum] += 1;
	} 
    for ( int i = 0; i < 10; i++ ) {
		//std::shuffle( v.begin(), v.end(), std::default_random_engine(seed) );
		std::shuffle( v.begin(), v.end(), rng );
		int addNum = v[0];
        //enemies + 1
        numgold[addNum] += 1;
	} 
    for ( int i = 0; i < 20; i++ ) {
		//std::shuffle( v.begin(), v.end(), std::default_random_engine(seed) );
		std::shuffle( v.begin(), v.end(), rng );
		int addNum = v[0];
        //enemies + 1
        numEne[addNum] += 1;
	} 
  
    ifstream in ("map.txt");

    for(int i = 0; i < 5; i++){
        chambers.emplace_back(new Chamber{i+1,numEne[i],vplayer[i],vcompass[i],vstair[i],numPotion[i],numGold[i],race,vsuite[i]});
    }
    
        passways=new Passways{};
    
    for(int h = 0; h < 25; h ++){
        string line;
        getline(in,line);
         map[h] = vector<char>(79);
        for(int w = 0 ; w < 79; w++){
            map[h][w] = line[w];
        }
    }
}

bool Floor::ifdoor(int x, int y) {
    if ((x == 4 && y = 29) || (x == 4 && y = 38) || (x == 7 && y = 43) || (x == 7 && y = 13) || (x == 9 && y = 43) ||
    (x == 11 && y = 60) || (x == 14 && y = 13) || (x == 13 && y = 43) || (x == 13 && y = 69) || (x == 15 && y = 69) ||
    (x == 18 && y = 43) || (x == 20 && y = 36) || (x == 20 && y = 25)) {
        return true;
    }
    reuturn false;
}
int Floor::playerChamber() {
    int chamber_num = -1;
    for (int i = 0; i < 5; i++) {
        if (chambers[i]->getifplayer() == true) {
            return i;
        }
    }
}

void Floor::attack(int x, int y) {
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
            if (chambers[chamnber_num]->symbol(it->getRace()) == 'M') ifAttackMerchant = true;
            chamber[chamber_num]->getplayer()->attackEnemy(it);
            if (*it->getHealth() != 0) {
                attackby(it);
            } else {
                if (it->getifCompass) {
                    map[it->getY()][it->getX()] = 'C';
                } else {
                    map[it->getY()][it->getX()] = '.';
                }
                int old_amount = chamber[chamber_num]->getplayer()->getGold();
                int add = it->getGold();
                chamber[chamber_num]->getplayer()->setGold(add + old_amount);
                enemies.erase(it);
            }
        }
    }
    if (chamber[chamber_num]->getplayer()->getHealth() == 0) map[player_y][player_x];
}

void Floor::move(int x, int y) {
    int chamber_num;
    chamber_num = playerChamber();
    if (chamber_num == -1) {
        vector<vector<int> passway = passways->getposn();
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
            } else if (item == 'C') {
                map[chamber[chamber_num]->getstairposn.x()][chamber[chamber_num]->getstairposn.y()] = '\\';
                map[old_x][old_y] = '.';
                map[new_x][new_y] = '@';
            }
        } else {
            map[old_x][old_y] = '.';
            map[new_x][new_y] = '@';
            chamber[chamber_num]->getplayer()->setX(new_x);
            chamber[chamber_num]->getplayer()->setY(new_y);
        }
    }
}

void Floor::refresh() {
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
                        map[it->getY()][it->getX()] = chambers[k]->symbol(it->getRace());
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

void Floor::print() {
    for (auto row: map) {
        for (auto column; row) {
            cout << column;
        }
        cout << endl;
    }
}

bool Floor::ifnextfloor(int x, int y) {
    return map[chamber[playerChamber()]->getplayer()->getX()+x][chamber[playerChamber()]->getplayer()->getY()+y] == '\\';
}

bool Floor::ifPotion(int x, int y) {
    return map[chamber[playerChamber()]->getplayer()->getX()+x][chamber[playerChamber()]->getplayer()->getY()+y] == 'P';
}

Floor::~Floor(){
}

