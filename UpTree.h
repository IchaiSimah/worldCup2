#ifndef UP_TREE_H_
#define UP_TREE_H_
#include "wet2util.h"

class Player;
class Team;

class NodeInUT{
private:
    int id;
    Player* player;
    NodeInUT* leader;
    Team* team;
    int gamesPlayed;
    permutation_t internSpirit;
public: 
    NodeInUT(int id, Player* player, NodeInUT* leader, Team* team, int gamesPlayed, 
                                const permutation_t internSpirit);
    permutation_t getInternSpirit()const;
    void addMatch(int i = 1);
    int getGamesPlayed()const;
    NodeInUT* getLeader()const;
    void setInternSpirit(permutation_t &spirit);
    void setLeader(NodeInUT* newLeader);
    void setGamePlayed(int num);
    void treeContraction();
    Team* getTeam();
};

// Class UpTree{
//     private:
    
// }






#endif //UP_TREE_H_