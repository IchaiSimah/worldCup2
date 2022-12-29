#include "Player.h"

Player::Player(int id, permutation_t spirit, int gamesplayed, int ability, int cards, bool goalKeeper):
id(id),spirit(spirit), gamesPlayed(gamesplayed), ability(ability),cards(cards), goalKeeper(goalKeeper){}

void Player::addCards(int cardsToAdd){
    cards+=cardsToAdd;
}
int Player::getCards(){
    return cards;
}
NodeInUT* Player::getNode(){
    return nodeInUT;
}
int Player::getAbility()const{
    return ability;
}
bool Player::isGoalKeeper()const{
    return goalKeeper;
}

int Player::getTotalPlayedGames(){
    NodeInUT* tmpNode = nodeInUT;
    int playedGames = 0;
    while (tmpNode){
		playedGames+= tmpNode->getGamesPlayed();
		tmpNode = tmpNode->getFather();
	}
}