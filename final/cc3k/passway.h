#ifndef _PASSWAY_H_
#define _PASSWAY_H_
#include <vector>
using namespace std;
class Passways{

    private:
    vector<vector <int> > posn;
    player* curplayer;
    public:
    vector<vector <int> > getposn();
    player* getplayer();
    Passways();
    ~Passways();
};

#endif