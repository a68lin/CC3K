#include "myplayer.h"

Player::Player(int a, int b, int c, PlayerType d) {
    this->hp = a;
    this->attack = b;
    this->defence = c;
    this->race = d;
}

int Player::getDefence() {
    return defence;
}

int Player::getAttack() {
    return attack;
}

int Player::getHp() {
    return hp;
}

PlayerType Player::getRace() {
    return race;
}

void Player::enhanceDefence(int b) {
    this->defence = b;
}

void Player::enhanceAttack(int c) {
    this->attack = c;
}

void Player::enhanceHealth(int d) {
    this->hp = d;
}



