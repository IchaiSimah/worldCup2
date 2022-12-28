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
    int internSpirit;
    int numOfPlayers;
};






#endif //UP_TREE_H_