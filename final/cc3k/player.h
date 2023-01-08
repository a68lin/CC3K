
#ifndef _PLAYER_
#define _PLAYER_
#include "character.h"
#include "enemy.h"
#include <tgmath.h>

class player : public character {
  bool ifBarrier = false;
//  basePotions* potions = nullptr;
public:
  player(CharType race, int health, int attack, int defence, int gold,
  int x, int y, bool ifCompass);
  void move(int, int);
  void enhanceAttack(int new_attack);
  void enhanceDefence(int new_defence);
  void attackby( enemy& );
  void attackEnemy( enemy& );
  void getifBarrier();
  void setifBarrier(bool);
  ~player();
};

#endif
