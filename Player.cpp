#include "Player.h"

Player::Player(int id, int ability, int cards, bool goalKeeper): id(id),
                                                                 ability(ability),
                                                                 cards(cards),
                                                                 goalKeeper(goalKeeper),
                                                                 nodeInUT(nullptr){}
Player::~Player() {
    if(nodeInUT){
        delete nodeInUT;
    }
}
void Player::addCards(int cardsToAdd){
        cards+=cardsToAdd;
    }

int Player::getCards(){
        return cards;
    }

NodeInUT* Player::getNode(){
     return nodeInUT;
    }


bool Player::isGoalKeeper()const{
        return goalKeeper;
    }



void Player::setNode(NodeInUT *node) {
    nodeInUT=node;
}

int Player::getPlayerId() {
    return id;
}
