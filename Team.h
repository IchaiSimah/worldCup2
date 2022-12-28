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

public:
    Team(int teamId): id(teamId){}
    void addCards(int i);
    int getGamePlayed();
    bool isInGame();
};


#endif //TEAM_H_