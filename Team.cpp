#include "Team.h"
Team::Team(int teamId):id(teamId),
                       leader(nullptr),
                       numOfGoalKeepers(0),
                       totalAbility(0),
                       totalSpirit((new permutation_t)->neutral()),
                       totalCards(0),
                       inGame(true),
                       points(0),
                       numOfPlayers(0){
    abilityId = AbilityId(0,id);
}

void Team::updateStats(Player* player, const permutation_t& spirit, int ability){
    if(!leader){
		leader = player;
	}
	if(player->isGoalKeeper()){
		numOfGoalKeepers++;
	}
	totalAbility+=ability;
    numOfPlayers++;
    totalSpirit = totalSpirit * spirit;
    abilityId = AbilityId(totalAbility,id);
}


void Team::addCards(int i){
    totalCards+=i;
}

bool Team::isInGame()const{
    return inGame;
}
Player* Team::getLeader()const{
    return leader;
}
void Team::addSpirit(const permutation_t& spirit){
    totalSpirit = totalSpirit * spirit;
}
permutation_t Team::getTotalSpirit()const{
    return totalSpirit;
}
void Team::setLeader(Player* player){
    leader = player;
}
void Team::addGoalKeeper(int num){
    numOfGoalKeepers += num;
}
void Team::addAbility(int ability){
    totalAbility+=ability;
    abilityId = AbilityId(totalAbility, id);
}
bool Team::canPlay()const{
    return numOfGoalKeepers;
}
int Team::getTotalAbility()const{
    return totalAbility;
}
int Team::getPoints()const{
    return points;
}
void Team::addPoints(int pointsToAdd){
    points+= pointsToAdd;
}
void Team::increaseNumOfPlayers(int num){
    numOfPlayers+=num;
}
int Team::getNumOfPlayers()const{
    return numOfPlayers;
}
int Team::getTotalCards()const{
    return totalCards;
}
int Team::getNumOfGK()const{
    return numOfGoalKeepers;
}

void Team::setNodeAbility(Node<int, Team*>* node) {
    nodeAbility=node;
}

int Team::getId() {
    return id;
}

AbilityId Team::getAbilityId() {
    return abilityId;
}

void Team::loose() {
    inGame= false;
}
