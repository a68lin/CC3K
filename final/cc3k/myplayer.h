#ifndef __MYPLAYER_H__
#define __MYPLAYER_H__

enum class PlayerType{Human, Dwarf, Elves, Orc};

class Player {
protected:
    int defence;
    int attack;
    int hp;
    PlayerType race;
public:
    Player(int, int, int, PlayerType);
    int getDefence();
    int getAttack();
    int getHp();
    PlayerType getRace();
    void enhanceDefence(int);
    void enhanceAttack(int);
    void enhanceHealth(int);
};
#endif


