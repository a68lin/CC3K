#include "cc3k.h"

std::vector<int> direction(char a, char b) {
    int x;
    int y;
    int success = 1;
    if (a == 'n' && b == 'o') {
        x = -1;
        y = 0;
    } else if (a == 's' && b == 'o') {
        x = 1;
        y = 0;
    } else if (a == 'e' && b == 'a') {
        x = 0;
        y = 1;
    } else if (a == 'w' && b == 'e') {
        x = 0;
        y = -1;
    } else if (a == 'n' && b == 'e') {
        x = -1;
        y = 1;
    } else if (a == 'n' && b == 'w') {
        x = -1;
        y = -1;
    } else if (a == 's' && b == 'e') {
        x = 1;
        y = 1;
    } else if (a == 's' && b == 'w') {
        x = 1;
        y = -1;
    } else {
        success = 0;
    }
    std::vector<int> result{y, x, success};
    return result;
}

int main( int argc, char * argv[] ) {
    char race; 
    int numfloor = 1;
    cc3k game{};
    if (argc > 1) {
        std::string filename = argv[1];
        ifstream map = filename;
        game.setMap(map);
    }
    char cmd;
    if (!std::cin >> cmd)  return;
    if (cmd != 'h' && cmd != 'e' && cmd != 'd' && cmd != 'o') return;
    if (cmd == 'p') return;
    game.init(cmd);
    race = cmd;
    game.print();
    char northSouth;
    char eastWest;
    std::cin >> cmd;
    while (std::cin >> cmd) {
        if (cmd == 'r') {
            game.reset();
            if (!std::cin >> cmd)  return;
            if (cmd != 'h' && cmd != 'e' && cmd != 'd' && cmd != 'o') return;
            game.init(cmd);
            race = cmd;
        } else if (cmd == 'u') {
            if (!std::cin >> northSouth >> eastWest) return;
            vector<int> result = direction(northSouth, eastWest);
            if (!result[2]) return;
            if (!game.ifPotion(result[0], result[1])) continue;
            game.move(result[0], result[1]);
        } else if (cmd == 'a') {
            if (!std::cin >> northSouth >> eastWest) return;
            vector<int> result = direction(northSouth, eastWest);
            if (!result[2]) return;
            game.attack(result[0], result[1]);
        } else if (cmd == 'q') {
            return;
        } else {
            if (!std::cin >> northSouth >> eastWest) return;
            vector<int> result = direction(northSouth, eastWest);
            if (!result[2]) return;
            if (game.ifnextfloor(result[0], result[1])) {
                if (numfloor == 5) {
                    return;
                } else {
                    game.reset();
                    game.init(race);
                    numfloor += 1;
                }
            }
            game.move(result[0], result[1]);
        }
        game.print();
    }
}