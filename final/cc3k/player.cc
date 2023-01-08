#include "player.h"
using namespace std;

player::player(CharType race, int health, int attack, int defence, int gold,
  int x, int y, bool ifCompass): character(race, health, attack, defence, gold,
  x, y, ifCompass) {}

void player::move(int x, int y) {
    this->x = x;
    this->y = y;
  }

void player::enhanceAttack(int new_attack) {
  attack = new_attack;
}

void player::enhanceDefence(int new_defence) {
  defence = new_defence;
}

void player::attackby(enemy& enemy) {
  int damage; 
  damage = ceil(100 * enemy.getAttack()/(100 + defence));
  if (ifBarrier == true) damage = ceil(damage / 2);
  health -= damage;
  if (health < 0) health = 0;
}

void player::attackEnemy(enemy& enemy) {
  int damage;
  damage = ceil(100 * attack/(100 + enemy.getDefence()));
  int enemy_health = enemy.getHealth() - damage;
  if (enemy_health < 0) enemy_health = 0;
  enemy.setHealth(enemy_health);
}

bool player::getifBarrier() {
  return ifBarrier;
}

void player::setifBarrier(bool new) {
  ifBarrier = new;
}

player::~player() {}