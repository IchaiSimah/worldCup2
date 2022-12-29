#ifndef TEAM_H_
#define TEAM_H_

#include"Player.h"
#include "wet2util.h"

class Team{
private:
    int id;
    Player* leader;
    int numOfGoalKeepers;
    int totalAbility;
    permutation_t totalSpirit;
    int totalCards;
    bool inGame = true;
    int points;
    int numOfPlayers;
public:
    Team(int teamId);
    void addCards(int i);
    bool isInGame()const;
    Player* getLeader()const;
    void addSpirit(const permutation_t& spirit);
    permutation_t getTotalSpirit()const;
    void setLeader(Player* player);
    void addGoalKeeper(int num = 1);
    void addAbility(int ability);
    void addPlayer(Player& player);
    bool canPlay()const;
    int getTotalAbility()const;
    int getPoints()const;
    void addPoints(int pointsToAdd);
    void addPlayers(int num);
    int getNumOfPlayers()const;
    int getTotalCards()const;
    int getNumOfGK()const;
};


#endif //TEAM_H_