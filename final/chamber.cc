#include "chamber.h"
using namespace std;

chamber::chamber(int number): number{number} {
    if (number == 1) {
        for (int i = 3; i <= 6; i++) {
            for (int j = 3; j <= 28; j++) {
                vector<int> posn{i, j};
                tile.emplace_back(posn);
            }
        }
    }
    if (number == 2) {
        for (int i = 39; i <= 60; i++) {
            vector<int> posn{3, i};
            tile.emplace_back(posn);
        }
        for (int i = 39; i <= 61; i++) {
            vector<int> posn{4, i};
            tile.emplace_back(posn);
        }
        for (int i = 39; i <= 68; i++) {
            vector<int> posn{5, i};
            tile.emplace_back(posn);
        }
        for (int i = 39; i <= 72; i++) {
            vector<int> posn{6, i};
            tile.emplace_back(posn);
        }
        for (int i = 7; i <= 12; i++) {
            for (int j = 61; j <= 75; j++) {
                vector<int> posn{i, j};
                tile.emplace_back(posn);
            }
        }
    }
    if (number == 3) {
        for (int i = 10; i <= 12; i++) {
            for (int j = 38; j <= 49; j++) {
                vector<int> posn{i, j};
                tile.emplace_back(posn);
            }
        }

    }
    if (number == 4) {
        for (int i = 15; i <= 21; i++) {
            for (int j = 4; j <= 24; j++) {
                vector<int> posn{i, j};
                tile.emplace_back(posn);
            }
        }
    }
    if (number == 5) {
        for (int i = 65; i <= 75; i++) {
            vector<int> posn1{16, i};
            vector<int> posn2{17, i};
            vector<int> posn3{18, i};
            tile.emplace_back(posn1);
            tile.emplace_back(posn2);
            tile.emplace_back(posn3);
        }
        for (int i = 19; i <= 21; i++) {
            for (int j = 37; j <= 75; j++) {
                vector<int> posn{i, j};
                tile.emplace_back(posn);
            }
        }
    }
}

vector<vector<int>> chamber::getTile() {
    return tile;
}