#include "cc3k.h"

cc3k::cc3k(): board{nullptr} {}

void cc3k::init(char race) {
    board = new Floor(race);
}

void cc3k::reset() {
    delete board;
    board = nullptr;
}

void cc3k::usePotion(int x, int y) {
    board->usePotion(x, y);
}

void cc3k::attack(int x, int y) {
    board->attack(x, int y);
}

void cc3k::move(int x, int y) {
    board->move(x, y);
}

void cc3k::print() {
    board->print();
    board->refresh();
}

bool cc3k::ifnextfloor(int x, int, y) {
    board->ifnetfloor(x, y);
}

bool cc3k::ifPotion(int x, int y) {
    board->ifPotion(int x, int y);
}
