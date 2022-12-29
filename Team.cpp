#include "Team.h"

void Team::addPlayer(Player& player){
    if(!leader){
		leader = &player;
	}
	if(player.isGoalKeeper()){
		numOfGoalKeepers++;
	}
	totalAbility+=player.getAbility();
    numOfPlayers++;
}