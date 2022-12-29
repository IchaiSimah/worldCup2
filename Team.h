#ifndef TEAM_H_
#define TEAM_H_

#include"Player.h"

class Team{
private:
    int id;
    Player* leader;
    int numOfGoalKeepers;
    int totalAbility;
    bool inGame = true;
    int points;
    int numOfPlayers;
public:
    Team(int teamId): id(teamId){}
    void addCards(int i);
    int getGamePlayed();
    bool isInGame();
    Player* getLeader();
    void addSpirit(const permutation_t& spirit);
    permutation_t getTotalSpirit();
    void setLeader(Player* player);
    void addGoalKeeper(int num = 1);
    void addAbility(int ability);
    void addPlayer(Player& player);
    bool canPlay()const;
    int getTotalAbility()const;
    int getPoints()const;
    void addPoints(int points);
    void addPlayers(int num);
    int getNumOfPlayers()const;
    int getTotalCards()const;
    int getNumOfGK()const;
};


#endif //TEAM_H_