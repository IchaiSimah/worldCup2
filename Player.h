#ifndef PLAYER_H_
#define PLAYER_H_

#include "wet2util.h"
#include "UpTree.h"

class Player{
private:
    int id;
    permutation_t spirit;
    int gamesPlayed;
    int ability;
    int cards;
    bool goalKeeper;
    NodeInUT nodeInUT;
public:
    Player(int id, permutation_t spirit, int gamesplayed, int ability, int cards, bool goalKeeper);
};



#endif //PLAYER_H_