#ifndef UP_TREE_H_
#define UP_TREE_H_


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
                                const permutation_t internSpirit, int numOfPlayers);
    permutation_t getInternSpirit();
    void addMatch(int i = 1);
    int getGamesPlayed();
    NodeInUT* getLeader()const;
    void setInternSpirit(permutation_t &spirit);
    void setLeader(const NodeInUT* leader);
};

// Class UpTree{
//     private:
    
// }






#endif //UP_TREE_H_