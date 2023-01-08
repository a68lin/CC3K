#ifndef _CHAMBER_H_
#define _CHAMBER_H_
#include <vector>
#include "character.h"
#include "basepotion.h"
#include "treasure.h"
#include "enemyFactory"
#include "playerFactory"
using namespace std;
class Chamber{
    int numEnemy;
    int numChamber;
    int numGold;
    int numdragon;
    bool ifplayer;
    bool ifcompass;
    bool ifstair;
    int numPotion;
    char race;
    player* curplayer;
    struct potionposn{
        int x;
        int y;
    };
    struct goldposn{
        int x;
        int y;
    };
    struct stairposn{
        int x;
        int y;
    };
    bool ifsuite;
    vector<enemy*> enemies;
    vector<treasure*> goldPile;
    vector<Potion*> potions;
    vector<gold*> golds;
    public:
    bool getifplayer();
    bool getifcompass();
    bool getifstair();
    void createGold(int,int,int);
    vector<enemy*> getEnemies();
    vector<treasure*> getTreasure();
    vector<Potion*> getPotions();
    vector<gold*> getGold();
    player* getplayer();
    potionposn getpotionposn();
    goldposn getgoldposn();
    stairposn getstairposn();
    int getnumene();
    int getnumpotion();
    Chamber(int,int,bool,bool,bool,int,int,char,bool);
    ~Chamber();
    int randomPos(int,int) const;
    void createPlayer(int,int,char);
    void createEnemy(int,int,char);
    void createPotion(int,int,string);
    char symbol(charType character);
};

#endif