#ifndef TEAM_H_
#define TEAM_H_

#include"Player.h"

class Team{
private:
    int id;
    Player* leader;
    int numOfGoalKeepers;
    int totalAbility;

public:
    Team(int teamId): id(teamId){}
    void addCards();
    int getGamePlayed();
};


#endif //TEAM_H_