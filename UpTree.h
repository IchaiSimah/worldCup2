#ifndef UP_TREE_H_
#define UP_TREE_H_

#include "Player.h"
#include "Team.h"
struct NodeInUT
{
    int id;
    Player* player;
    NodeInUT* leader;
    Team* team;
    int gamesPlayed;
    int internSpirit;
    int numOfPlayers;
};






#endif //UP_TREE_H_