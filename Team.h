#ifndef TEAM_H_
#define TEAM_H_

#include"Player.h"
#include "AVL_TREE_TEMPLATE.h"
#include "wet2util.h"




class AbilityId{
public:
    int ability;
    int id;
    AbilityId(int ability=0, int id=0): ability(ability), id(id){}

    bool operator==(AbilityId a){
        if (a.ability==ability && a.id==id) return true;
        return false;
    }

    bool operator> (AbilityId a){
        if (ability>a.ability) return true;
        if (ability==a.ability && id>a.id) return true;
        return false;
    }

    bool operator<(AbilityId a){
        return (!(*this>a)&& !(*this==a));
    }

};

class Team{
private:
    int id;
    Player* leader;
    int numOfGoalKeepers;
    int totalAbility;
    AbilityId abilityId;
    permutation_t totalSpirit;
    int totalCards;
    bool inGame = true;
    int points;
    int numOfPlayers;

public:
    Team(int teamId);
    void addCards(int i);
    void addGoalKeeper(int num = 1);
    void addAbility(int ability);
    void updateStats(Player* player, const permutation_t& spirit, int ability);
    void setLeader(Player* player);
    void addSpirit(const permutation_t& spirit);
    void addPoints(int pointsToAdd);
    void increaseNumOfPlayers(int num);

    void loose();
    bool isInGame()const;
    Player* getLeader()const;
    permutation_t getTotalSpirit()const;
    bool canPlay()const;
    int getId();
    int getTotalAbility()const;
    AbilityId getAbilityId();
    int getPoints()const;
    int getNumOfPlayers()const;
    int getTotalCards()const;
    int getNumOfGK()const;
};


#endif //TEAM_H_