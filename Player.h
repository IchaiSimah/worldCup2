#ifndef PLAYER_H_
#define PLAYER_H_

#include "wet2util.h"
#include "UpTree.h"


class Player{
private:

    int ability;
    int cards;
    bool goalKeeper;
    NodeInUT* nodeInUT;

public:
    Player(int ability=0, int cards=0, bool goalKeeper=false);
    void addCards(int cardsToAdd);
    void setNode(NodeInUT* node);

    int getCards();
    NodeInUT* getNode();
    int getAbility()const;
    bool isGoalKeeper()const;
    int getTotalPlayedGames();
};



#endif //PLAYER_H_