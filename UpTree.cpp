#include "UpTree.h"
    // int id;
    // Player* player;
    // NodeInUT* leader;
    // Team* team;
    // int gamesPlayed;
    // permutation_t internSpirit;
NodeInUT::NodeInUT(int id, Player* player, NodeInUT* leader, Team* team, int gamesPlayed, 
                        const permutation_t internSpirit): id(id),
                                                                            player(player),
                                                                            leader(leader),
                                                                            team(team),
                                                                            gamesPlayed(gamesPlayed),
                                                                            internSpirit(internSpirit)
{}

void NodeInUT::treeContraction(){
	NodeInUT* leaderFinder = this;
    int newPlayedgames = gamesPlayed;
    permutation_t newInternSpirit = internSpirit;
    while (leaderFinder -> leader)
    {
        leaderFinder = leaderFinder->leader;
        newPlayedgames += leaderFinder->gamesPlayed;
        newInternSpirit = leaderFinder->internSpirit * newInternSpirit;
    }
    NodeInUT* tmpNode = this;
    while (tmpNode->leader != leaderFinder){
        int tmpGamesPlayed = tmpNode->gamesPlayed;
        permutation_t tmpInternSpirit = tmpNode ->internSpirit;
        tmpNode->gamesPlayed = newPlayedgames - leader->gamesPlayed;
        tmpNode->internSpirit = leader->internSpirit.inv() * newInternSpirit;
        newPlayedgames-=tmpGamesPlayed;
        newInternSpirit = newInternSpirit * tmpInternSpirit.inv();
        tmpNode->leader = leaderFinder;
    }
}


    permutation_t NodeInUT::getInternSpirit()const{
        return internSpirit;
    }
    void NodeInUT::addMatch(int i = 1){
        gamesPlayed += i;
    }
    int NodeInUT::getGamesPlayed()const{
        return gamesPlayed;
    }
    NodeInUT* NodeInUT::getLeader()const{
        return leader;
    }
    void NodeInUT::setInternSpirit(permutation_t &spirit){
        internSpirit = spirit;
    }
    void NodeInUT::setLeader(NodeInUT* newLeader){
        leader = newLeader;
    }
    void NodeInUT::setGamePlayed(int num){
        gamesPlayed = num;
    }
    Team* NodeInUT::getTeam(){
        return team;
    }