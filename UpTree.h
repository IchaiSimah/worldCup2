#ifndef UP_TREE_H_
#define UP_TREE_H_
#include "wet2util.h"
#include "Team.h"

class Player;


class NodeInUT{
private:
    int id;
    int gamesPlayed;
    permutation_t internSpirit;

    Player* player;
    NodeInUT* father;
    Team* team;

public: 
    NodeInUT(int id,  int gamesPlayed, const permutation_t& internSpirit, Player* player, NodeInUT* father, Team* team);
    permutation_t getInternSpirit()const;

    void addMatch(int i = 1);
    void setInternSpirit(permutation_t &spirit);
    void setLeader(NodeInUT* newFather);
    void setTeam(Team* newTeam);
    void setGamePlayed(int num);

    int getGamesPlayed()const;
    NodeInUT* getFather()const;
    Player* getPlayer()const;
    Team* getTeam();
    int getId();

    void treeContraction();
};


#endif //UP_TREE_H_