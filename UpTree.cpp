#include "UpTree.h"


NodeInUT::NodeInUT(int id,  int gamesPlayed, const permutation_t& internSpirit, Player* player, NodeInUT* father, Team* team):
                                                                                id(id),
                                                                                gamesPlayed(gamesPlayed),
                                                                                internSpirit(internSpirit),
                                                                                player(player),
                                                                                father(father),
                                                                                team(team)
                                                                                {}

NodeInUT::~NodeInUT(){
    if(!father){
        delete team;
    }
}
void NodeInUT::treeContraction(){
	NodeInUT* leaderFinder = this;
    int newPlayedGames = gamesPlayed;
    permutation_t newInternSpirit = internSpirit;
    while (leaderFinder -> father){
        leaderFinder = leaderFinder->father;
        newPlayedGames += leaderFinder->gamesPlayed;
        newInternSpirit = leaderFinder->internSpirit * newInternSpirit;
    }
    NodeInUT* tmpNode = this;

    while (tmpNode->father != leaderFinder){
        int tmpGamesPlayed = tmpNode->gamesPlayed;
        permutation_t tmpInternSpirit = tmpNode ->internSpirit;
        tmpNode->gamesPlayed = newPlayedGames - leaderFinder->gamesPlayed;
        tmpNode->internSpirit = leaderFinder->internSpirit.inv() * newInternSpirit;
        newPlayedGames-=tmpGamesPlayed;
        newInternSpirit = newInternSpirit * tmpInternSpirit.inv();
        NodeInUT* fatherNode = tmpNode->father;
        tmpNode->father = leaderFinder;
        tmpNode = fatherNode;
    }
}


permutation_t NodeInUT::getInternSpirit()const{
        return internSpirit;
    }


void NodeInUT::addMatch(int i){
        gamesPlayed += i;
    }


int NodeInUT::getGamesPlayed()const{
        return gamesPlayed;
    }


NodeInUT* NodeInUT::getFather()const{
        return father;
}


void NodeInUT::setInternSpirit(permutation_t &spirit){
        internSpirit = spirit;
    }


void NodeInUT::setLeader(NodeInUT* newFather){
    father = newFather;
    }

void NodeInUT::setTeam(Team* newTeam){
    team=newTeam;
}
void NodeInUT::setGamePlayed(int num){
        gamesPlayed = num;
    }


Team* NodeInUT::getTeam(){
        return team;
    }

Player *NodeInUT::getPlayer() const {
    return player;
}

int NodeInUT::getId() {
    return id;
}
