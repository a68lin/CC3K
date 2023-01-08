#include "chamber.h"
using namespace std;

int main() {
    bool same = false;
    chamber a(1);
    chamber b(2);
    chamber c(3);
    chamber d(4);
    chamber e(5);
    vector<vector<int>> av = a.getTile();
    vector<vector<int>> bv = b.getTile();
    vector<vector<int>> cv = c.getTile();
    vector<vector<int>> dv = d.getTile();
    vector<vector<int>> ev = e.getTile();
    for (int i = 0; i <= 24; i++) {
        for (int j = 0; j <= 78; j++) {
            vector<int> posn{i, j};
            for (auto it: av) {
                if (posn == it) same = true;
            }
            for (auto it: bv) {
                if (posn == it) same = true;
            }
            for (auto it: cv) {
                if (posn == it) same = true;
            }
            for (auto it: dv) {
                if (posn == it) same = true;
            }
            for (auto it: ev) {
                if (posn == it) same = true;
            }
            if (same == true) {
                std::cout << '.';
            } else {
                std::cout << ' ';
            }
            same = false;
        }
        std::cout << std::endl;
    }
}