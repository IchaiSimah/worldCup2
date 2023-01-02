#ifndef UP_TREE_H_
#define UP_TREE_H_
#include "wet2util.h"
#include <memory>


class Player;
class Team;

class NodeInUT{
private:
    int id;
    int gamesPlayed;
    permutation_t internSpirit;

    Player* player;
    NodeInUT* father;
    std::shared_ptr<Team> team;

public: 
    NodeInUT(int id,  int gamesPlayed, const permutation_t& internSpirit, Player* player, NodeInUT* father, std::shared_ptr<Team> team);
    permutation_t getInternSpirit()const;

    void addMatch(int i = 1);
    void setInternSpirit(permutation_t &spirit);
    void setLeader(NodeInUT* newFather);
    void setTeam(std::shared_ptr<Team> newTeam);
    void setGamePlayed(int num);

    int getGamesPlayed()const;
    NodeInUT* getFather()const;
    Player* getPlayer()const;
    std::shared_ptr<Team> getTeam();
    int getId();

    void treeContraction();
};


#endif //UP_TREE_H_