#ifndef PLAYER_H_
#define PLAYER_H_

#include "wet2util.h"
#include "UpTree.h"


class Player{
private:
    int id;
    int ability;
    int cards;
    bool goalKeeper;
    NodeInUT* nodeInUT;

public:
    Player(int id=0, int ability=0, int cards=0, bool goalKeeper=false);
    ~Player();
    void addCards(int cardsToAdd);
    void setNode(NodeInUT* node);

    int getCards();
    int getPlayerId();
    NodeInUT* getNode();
    bool isGoalKeeper()const;
};



#endif //PLAYER_H_