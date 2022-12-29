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
    NodeInUT* nodeInUT;
public:
    Player(int id, permutation_t spirit=permutation_t(0), int gamesplayed=0, int ability=0, int cards=0, bool goalKeeper=false);
    void addCards(int cardsToAdd);
    int getCards();
    NodeInUT* getNode();
    int getAbility()const;
    bool isGoalKeeper()const;
    int getTotalPlayedGames();
    
};



#endif //PLAYER_H_