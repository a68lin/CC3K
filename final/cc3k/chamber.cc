#include "chamber.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
//output a random number
int Chamber::randomPos(int min,int max)const{
      vector<int> v;
      for(int i = min; i <= max; i++){
          v.emplace_back(i);
      }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
	std::shuffle( v.begin(), v.end(), rng );
    return v[0];
}

//create a player
void Chamber::createPlayer(int xpos, int ypos,char race){
    if(race == 'h'){
                curplayer = createHuman(xpos,ypos);
    }else if (race == 'e'){
                curplayer = createElf(xpos,ypos);
    }else if (race == 'd'){
                curplayer = createDwarf(xpos,ypos);
    }else if(race == 'o'){
                curplayer = createOrc(xpos,ypos);
    }
}
//create a gold
void Chamber::createGold(int xpos,int ypos,char rGold){
    switch (rGold)
                {
                case 'n':golds.emplace_back(Normal(xpos,ypos,1));
                    break;
                case 's':golds.emplace_back(Small(xpos,ypos,2));
                    break;
                case 'd':
                if(ifsuite){
                    golds.emplace_back(DragonHorde(xpos,ypos,0,true,true));
                    ifsuite = false;
                }else {
                    golds.emplace_back(DragonHorde(xpos,ypos,6,true,false));
                }
                    break;
}

//create an enemy
void Chamber::createEnemy(int xpos,int ypos, char enerace){
    switch (enerace)
                {
                case 'w':enemies.emplace_back(createWerewolf(xpos,ypos,false));
                    break;
                case 'v':enemies.emplace_back(cretaeVampire(xpos,ypos,false));
                    break;
                case 'g':enemies.emplace_back(createGoblin(xpos,ypos,false));
                    break;
                case 't':enemies.emplace_back(createTroll(xpos,ypos,false));
                    break;
                case 'p':enemies.emplace_back(createPhoenix(xpos,ypos,false));
                    break;
                case 'm':enemies.emplace_back(createMerchant(xpos,ypos,false));
                    break;
                }
}

//create a potion
void Chamber::createPotion(int xpos,int ypos, string prace){
    Potion* mypotion = new BasePotion(xpos,ypos);
    switch (prace)
    {
                case "subDefence": mypotion = new DefencePotion(mypotion, -5);
                potions.emplace_back(mypotion);
                    break;
                case "addDefence": mypotion = new DefencePotion(mypotion, 5);
                potions.emplace_back(mypotion);
                    break;
                case "subAttack": mypotion = new AttackPotion(mypotion, -5);
                potions.emplace_back(mypotion);
                    break;
                case "addAttack": mypotion = new AttackPotion(mypotion, 5);
                potions.emplace_back(mypotion);
                    break;
                case "subHealth": mypotion = new HealthPotion(mypotion, -10);
                potions.emplace_back(mypotion);
                    break;
                case "addHealth": mypotion = new HealthPotion(mypotion, 10);
                potions.emplace_back(mypotion);
                    break;
    }
}

player* Chamber::getplayer(){
    return curplayer;
}

potionposn Chamber::getpotionposn(){
    return potionposn;
}

goldposn Chamber::getgoldposn(){
    return goldposn;
}

stairposn Chamber::getstairposn(){
    return stairposn;
}

int Chamber::getnumene(){
    return numEnemy;
}

int Chamber::getnumpotion(){
    return numPotion;
}
Chamber::Chamber(int numch,int numEne,bool player,bool compass,bool stair,int potion,int gold,char race,bool suite):
ifplayer{player},ifcompass{compass},numChamber{numch},numEnemy{numEne},ifstair{stair},numPotion{potion},numGold{gold},ifsuite{suite}{
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    //make a player if nessecarry
    //factory
    enemyFactory EFA;
    playerFactory PFA;
    //generate random enemies
    vector<char> ene = {'w','w','w','w','v','v','v','g','g','g','g','g','t','t','p','p','m','m'};
    vector<string> pot = {"subDefence","subDefence","addDefence","addDefence","subAttack","subAttack","addAttack","addAttack","subHealth","subHealth","addHealth","addHealth"};
    vector<char> gol = {'n','n','n','n','n','d','s','s'};
    char enelist[numEnemy];
    string poslist[numPotion];
    char goldlist[numGold];
	std::shuffle( ene.begin(), ene.end(), rng );
    for (int i  = 0; i < numEnemy; i++){
        enelist[i] = ene[i];
    }
    std::shuffle( pot.begin(), pot.end(), rng );
    for (int i  = 0; i < numPotion; i++){
        poslist[i] = pot[i];
    }
    std::shuffle( gol.begin(), gol.end(), rng );
    for (int i  = 0; i < numGold; i++){
        goldlist[i] = pos[i];
    }
    //make an occupied list
    struct occupyposn {
        int x;
        int y;
    };
    vector<occupyposn> vecposn;
    int xpos;
    int ypos;
    bool validpos;
    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////
    //if in the first chamber
    if(numChamber == 1){
        //create player
        if(ifplayer){
            xpos  = Chamber::randomPos(3,28);
            ypos = Chamber::randomPos(3,6);
            createPlayer(xpos,ypos);
            vecposn.emplace_back(occupyposn{xpos,ypos});
        }
        //create stairways
        if(ifstair){
            xpos  = Chamber::randomPos(3,28);
            ypos = Chamber::randomPos(3,6);
            stairposn.x = xpos;
            stairposn.y = ypos;
            vecposn.emplace_back(occupyposn{xpos,ypos});
        }
        //create potions
        for(int i = 0; i < numPotion;i++){
            xpos  = Chamber::randomPos(3,28);
            ypos = Chamber::randomPos(3,6);
            createPotion(xpos,ypos,poslist[i]);
            vecposn.emplace_back(occupyposn{xpos,ypos});
        }
        //create gold
        for(int i = 0; i < numGold;i++){
            xpos  = Chamber::randomPos(3,28);
            ypos = Chamber::randomPos(3,6);
            createGold(xpos,ypos,goldlist[i]);
            vecposn.emplace_back(occupyposn{xpos,ypos});
        }
        //create enemys
        for(int i = 0; i < numEnemy; i ++){
            validpos = true;
            //make random position;
            xpos  = Chamber::randomPos(3,28);
            ypos = Chamber::randomPos(3,6);
            //check is occupied
            for(int a  = 0; a < vecposn.size(); a ++){
             if (xpos == vecposn[a].x && ypos == vecposn[a].y){
                    i -= 1;
                    validpos = false;
                    break;
                }
            }
            //if valid position create enemy
            if(validpos == true){
                vecposn.emplace_back(occupyposn{xpos,ypos});
                createEnemy(xpos,ypos, enelist[i]);
            }
        }
         ////////////////////////////////////////////////////////////////////
          ////////////////////////////////////////////////////////////////////
           ////////////////////////////////////////////////////////////////////
           //if in the second chamber
    }else if(numChamber == 2){
        //create players
        if(ifplayer){
             ypos = Chamber::randomPos(3,12);
            //different y position has different random x position
            if (ypos <= 4){
                xpos = Chamber::randomPos(39,61);
            }else if(ypos == 5){
                xpos = Chamber::randomPos(39,69);
            }else if (ypos == 6){
                xpos = Chamber::randomPos(39,72);
            }else {
                xpos = Chamber::randomPos(61,75);
            }
            createPlayer(xpos,ypos);
            vecposn.emplace_back(occupyposn{xpos,ypos});
        }
        //create stairs
        if(ifstair){
             ypos = Chamber::randomPos(3,12);
            //different y position has different random x position
            if (ypos <= 4){
                xpos = Chamber::randomPos(39,61);
            }else if(ypos == 5){
                xpos = Chamber::randomPos(39,69);
            }else if (ypos == 6){
                xpos = Chamber::randomPos(39,72);
            }else {
                xpos = Chamber::randomPos(61,75);
            }
            stairposn.x = xpos;
            stairposn.y = ypos;
            vecposn.emplace_back(occupyposn{xpos,ypos});
        }
        //create potions
        for(int i = 0; i < numPotion;i++){
             ypos = Chamber::randomPos(3,12);
            //different y position has different random x position
            if (ypos <= 4){
                xpos = Chamber::randomPos(39,61);
            }else if(ypos == 5){
                xpos = Chamber::randomPos(39,69);
            }else if (ypos == 6){
                xpos = Chamber::randomPos(39,72);
            }else {
                xpos = Chamber::randomPos(61,75);
            }
            vecposn.emplace_back(occupyposn{xpos,ypos});
            createPotion(xpos,ypos,poslist[i]);
        }
        //create gold
        for(int i = 0; i < numGold;i++){
            ypos = Chamber::randomPos(3,12);
            //different y position has different random x position
            if (ypos <= 4){
                xpos = Chamber::randomPos(39,61);
            }else if(ypos == 5){
                xpos = Chamber::randomPos(39,69);
            }else if (ypos == 6){
                xpos = Chamber::randomPos(39,72);
            }else {
                xpos = Chamber::randomPos(61,75);
            }
            createGold(xpos,ypos,goldlist[i]);
            vecposn.emplace_back(occupyposn{xpos,ypos});
        }
        //create enemies
        for(int i = 0; i < numEnemy; i ++){
            validpos = true;
            //make random position;
            ypos = Chamber::randomPos(3,12);
            //different y position has different random x position
            if (ypos <= 4){
                xpos = Chamber::randomPos(39,61);
            }else if(ypos == 5){
                xpos = Chamber::randomPos(39,69);
            }else if (ypos == 6){
                xpos = Chamber::randomPos(39,72);
            }else {
                xpos = Chamber::randomPos(61,75);
            }
            //check is occupied
            for(int a  = 0; a < vecposn.size(); a ++){
             if (xpos == vecposn[a].x && ypos == vecposn[a].y){
                    i -= 1;
                    validpos = false;
                    break;
                }
            }
            //if valid position create enemy
            if(validpos == true){
                vecposn.emplace_back(posn{xpos,ypos});
                createEnemy(xpos,ypos, enelist[i]);
            }
        }
         ////////////////////////////////////////////////////////////////////
         ////////////////////////////////////////////////////////////////////
          ////////////////////////////////////////////////////////////////////
          //as above
    }else if(numChamber == 3){
        if(ifplayer){
            xpos  = Chamber::randomPos(38,49);
            ypos = Chamber::randomPos(10,12);
            createPlayer(xpos,ypos);
            vecposn.emplace_back(occupyposn{xpos,ypos});
        }
        if(ifstair){
           xpos  = Chamber::randomPos(38,49);
            ypos = Chamber::randomPos(10,12);
            stairposn.x = xpos;
            stairposn.y = ypos;
            vecposn.emplace_back(occupyposn{xpos,ypos});
        }
        for(int i = 0; i < numPotion;i++){
            xpos  = Chamber::randomPos(38,49);
            ypos = Chamber::randomPos(10,12);
            createPotion(xpos,ypos,poslist[i]);
            vecposn.emplace_back(occupyposn{xpos,ypos});
        }
        //create gold
        for(int i = 0; i < numGold;i++){
            xpos  = Chamber::randomPos(38,49);
            ypos = Chamber::randomPos(10,12);
            createGold(xpos,ypos,goldlist[i]);
            vecposn.emplace_back(occupyposn{xpos,ypos});
        }
        for(int i = 0; i < numEnemy; i ++){
            validpos = true;
            //make random position;
            xpos  = Chamber::randomPos(38,49);
            ypos = Chamber::randomPos(10,12);
            //check is occupied
            for(int a  = 0; a < vecposn.size(); a ++){
             if (xpos == vecposn[a].x && ypos == vecposn[a].y){
                    i -= 1;
                    validpos = false;
                    break;
                }
            }
            //if valid position create enemy
            if(validpos == true){
                vecposn.emplace_back(posn{xpos,ypos});
               createEnemy(xpos,ypos, enelist[i]);
            }
        }
         ////////////////////////////////////////////////////////////////////
          ////////////////////////////////////////////////////////////////////
           ////////////////////////////////////////////////////////////////////
           //as above
    }else if(numChamber == 4){
        if(ifplayer){
            xpos  = Chamber::randomPos(4,24);
            ypos = Chamber::randomPos(15,21);
            createPlayer(xpos,ypos);
            vecposn.emplace_back(occupyposn{xpos,ypos});
        }
        if(ifstair){
           xpos  = Chamber::randomPos(4,24);
            ypos = Chamber::randomPos(15,21);
            stairposn.x = xpos;
            stairposn.y = ypos;
            vecposn.emplace_back(occupyposn{xpos,ypos});
        }
        for(int i = 0; i < numPotion;i++){
            xpos  = Chamber::randomPos(4,24);
            ypos = Chamber::randomPos(15,21);
            createPotion(xpos,ypos,poslist[i]);
            vecposn.emplace_back(occupyposn{xpos,ypos});
        }
        //create gold
        for(int i = 0; i < numGold;i++){
            xpos  = Chamber::randomPos(4,24);
            ypos = Chamber::randomPos(15,21);
            createGold(xpos,ypos,goldlist[i]);
            vecposn.emplace_back(occupyposn{xpos,ypos});
        }
        for(int i = 0; i < numEnemy; i ++){
            validpos = true;
            //make random position;
            xpos  = Chamber::randomPos(4,24);
            ypos = Chamber::randomPos(15,21);
            //check is occupied
            for(int a  = 0; a < vecposn.size(); a ++){
             if (xpos == vecposn[a].x && ypos == vecposn[a].y){
                    i -= 1;
                    validpos = false;
                    break;
                }
            }
            //if valid position create enemy
            if(validpos == true){
                vecposn.emplace_back(posn{xpos,ypos});
                createEnemy(xpos,ypos, enelist[i]);
            }
        }
         ////////////////////////////////////////////////////////////////////
          ////////////////////////////////////////////////////////////////////
           ////////////////////////////////////////////////////////////////////
           //as above
    }else if(numChamber == 5){
        if(ifplayer){
             ypos = Chamber::randomPos(16,21);
            //different y position has different random x position
            if (ypos <= 18){
                xpos = Chamber::randomPos(65,75);
            }else {
                xpos = Chamber::randomPos(37,75);
            }
            createPlayer(xpos,ypos);
            vecposn.emplace_back(occupyposn{xpos,ypos});
        }
        if(ifstair){
            ypos = Chamber::randomPos(16,21);
            //different y position has different random x position
            if (ypos <= 18){
                xpos = Chamber::randomPos(65,75);
            }else {
                xpos = Chamber::randomPos(37,75);
            }
            stairposn.x = xpos;
            stairposn.y = ypos;
            vecposn.emplace_back(occupyposn{xpos,ypos});
        }
        for(int i = 0; i < numPotion;i++){
             ypos = Chamber::randomPos(16,21);
            //different y position has different random x position
            if (ypos <= 18){
                xpos = Chamber::randomPos(65,75);
            }else {
                xpos = Chamber::randomPos(37,75);
            }
            vecposn.emplace_back(occupyposn{xpos,ypos});
            createPotion(xpos,ypos,poslist[i]);
        }
        //create gold
        for(int i = 0; i < numGold;i++){
             ypos = Chamber::randomPos(16,21);
            //different y position has different random x position
            if (ypos <= 18){
                xpos = Chamber::randomPos(65,75);
            }else {
                xpos = Chamber::randomPos(37,75);
            }
            createGold(xpos,ypos,goldlist[i]);
            vecposn.emplace_back(occupyposn{xpos,ypos});
        }
        for(int i = 0; i < numEnemy; i ++){
            validpos = true;
            //make random position;
            ypos = Chamber::randomPos(16,21);
            //different y position has different random x position
            if (ypos <= 18){
                xpos = Chamber::randomPos(65,75);
            }else {
                xpos = Chamber::randomPos(37,75);
            }
            //check is occupied
            for(int a  = 0; a < vecposn.size(); a ++){
             if (xpos == vecposn[a].x && ypos == vecposn[a].y){
                    i -= 1;
                    validpos = false;
                    break;
                }
            }
            //if valid position create enemy
            if(validpos == true){
                vecposn.emplace_back(posn{xpos,ypos});
                createEnemy(xpos,ypos, enelist[i]);
            }
        }
    }
    //create compass
    if(ifcompass){
        std::shuffle( enemies.begin(), enemies.end(), rng );
        enemies[0]->setCompass();
    }
}
bool Chamber::etifplayer(){
    return ifplayer;
}

bool Chamber::getifcompass(){
        return ifcompass;
}

bool Chamber::getifstair(){
        return ifstair;
}
vector<enemy*> Chamber::getEnemies(){
    return enemies;
}

vector<treasure*> Chamber::getTreasure(){
    return goldPile;
}

vector<Potion*> Chamber::getPotions(){
    return potions;
}

vector<gold*> Chamber::getGold(){
    return golds;
}

Chamber :: ~Chamber(){
    
    for(int i = 0; i < enemy.size(); i ++){
        delete enemy[i];
    }
    enemy.clear();
    for(int i = 0; i < golds.size(); i ++){
        delete golds[i];
    }
    goldPile.clear();
    for(int i = 0; i < potion.size(); i ++){
        delete potion[i];
    }
    potion.clear();
   
}

char Chamber::symbol(charType character) {
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

