#ifndef UP_TREE_H_
#define UP_TREE_H_
#include "wet2util.h"

class Player;
class Team;


class NodeInUT{
private:
    int id;
    int gamesPlayed;
    permutation_t internSpirit;
    Player* player;
    NodeInUT* leader;
    Team* team;

public: 
    NodeInUT(int id,  int gamesPlayed, const permutation_t internSpirit, Player* player, NodeInUT* leader, Team* team);
    permutation_t getInternSpirit()const;
    void addMatch(int i = 1);
    int getGamesPlayed()const;
    NodeInUT* getLeader()const;                             //it's the find function
    void setInternSpirit(permutation_t &spirit);
    void setLeader(NodeInUT* newLeader);
    void setGamePlayed(int num);
    void treeContraction();
    Team* getTeam();
};


#endif //UP_TREE_H_