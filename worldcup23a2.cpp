#include "worldcup23a2.h"


world_cup_t::world_cup_t(): AVL_team_by_id(AVL<int, Team *>()),
                            AVL_team_by_ability(AVL<AbilityId, Team*>()),
                            playersTable(HashTable<Player*>())
{
    NodeInLinkedList* newNode = new NodeInLinkedList;
    deletedTeams.first = newNode;
    deletedTeams.last = newNode;
}

world_cup_t::~world_cup_t(){
    AVL_team_by_id.clearData();
    NodeInLinkedList* tmpNode = deletedTeams.first->next;
    delete deletedTeams.first;
    while(tmpNode){
        NodeInLinkedList* toDeleteNode = tmpNode;
        tmpNode = tmpNode->next;
        delete toDeleteNode->data;
        delete toDeleteNode;
    }

}

StatusType world_cup_t::add_team(int teamId){
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (AVL_team_by_id.find(teamId)){
        return StatusType::FAILURE;
    }
    Team* new_team;
    try{
        new_team = new Team (teamId);
    } catch (const std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    AVL_team_by_id.insert(teamId, new_team);
    AVL_team_by_ability.insert(new_team->getAbilityId(), new_team);
    return StatusType::SUCCESS;
}


StatusType world_cup_t::remove_team(int teamId){
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (!AVL_team_by_id.find(teamId)){
        return StatusType::FAILURE;
    }
    Node<int, Team *>* to_delete = AVL_team_by_id.find(teamId);
    if (to_delete){
        to_delete->data->loose();
        AVL_team_by_ability.remove(to_delete->data->getAbilityId());
        AVL_team_by_id.remove(teamId);
        NodeInLinkedList* newNode = new NodeInLinkedList;
        newNode->data = to_delete->data;
        deletedTeams.last->next = newNode;
        deletedTeams.last = newNode;
        return  StatusType::SUCCESS;
    }
    return StatusType::FAILURE;
}


StatusType world_cup_t::add_player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper){

    if (playerId <= 0 || teamId <= 0 /*|| if spirit not good */ ||gamesPlayed < 0|| cards < 0 ) return StatusType::INVALID_INPUT;
    if (playersTable.find(playerId)!=-1 || AVL_team_by_id.find(teamId)== nullptr) return  StatusType::FAILURE;

	Team* team = AVL_team_by_id.find(teamId)->data;
    AVL_team_by_ability.remove(team->getAbilityId());
	Player* newPlayer= new Player(playerId, ability, cards, goalKeeper);
    team->updateStats(newPlayer, spirit, ability);
    AVL_team_by_ability.insert(team->getAbilityId(),team);
	permutation_t internSpirit = spirit;
    if (playerId != team->getLeader()->getPlayerId()) internSpirit= team->getLeader()->getNode()->getInternSpirit().inv() * team->getTotalSpirit();
	int tmpGamesPlayed = gamesPlayed;
    if (playerId != team->getLeader()->getPlayerId())tmpGamesPlayed = gamesPlayed - team->getLeader()->getNode()->getGamesPlayed();
	NodeInUT* newNode = new NodeInUT(playerId, tmpGamesPlayed, internSpirit, newPlayer, team->getLeader()->getNode(), team);
    newPlayer->setNode(newNode);
    playersTable.insert(playerId, newPlayer);
    return StatusType::SUCCESS;
}


output_t<int> world_cup_t::play_match(int teamId1, int teamId2){

    if (teamId1 <= 0 || teamId2 <= 0 ||teamId1 == teamId2) return StatusType::INVALID_INPUT;
	if(!AVL_team_by_id.find(teamId1)||!AVL_team_by_id.find(teamId2)) return  StatusType::FAILURE;
    int to_return =0;
	Team* team1 = AVL_team_by_id.find(teamId1)->data;
	Team* team2 = AVL_team_by_id.find(teamId2)->data;
	if(!team1->canPlay()||!team2->canPlay()) return  StatusType::FAILURE;

	team1->getLeader()->getNode()->addMatch();
	team2->getLeader()->getNode()->addMatch();
	Team* winner = nullptr;
	if(team1->getTotalAbility() + team1->getPoints() > team2->getTotalAbility() + team2->getPoints()){
		winner = team1;
        to_return = 1;
	}
	else if(team1->getTotalAbility() + team1->getPoints() < team2->getTotalAbility() + team2->getPoints()){
		winner = team2;
        to_return=3;
	}
	else if(team1->getTotalSpirit().strength() > team2->getTotalSpirit().strength()){
		winner = team1;
        to_return=2;

	}
	else if(team1->getTotalSpirit().strength() < team2->getTotalSpirit().strength()){
		winner = team2;
        to_return=4;
	}

	if(winner){
		winner->addPoints(3);
	}
	else{
        to_return = 0;
		team1->addPoints(1);
		team2->addPoints(1);
	}
	return to_return;
}


output_t<int> world_cup_t::num_played_games_for_player(int playerId){
    if (playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (playersTable.find(playerId) == -1){
        return StatusType::FAILURE;
    }

    NodeInUT* playerNode = playersTable.getT(playersTable.find(playerId))->getNode();
    if(!playerNode->getFather()){
        return playerNode->getGamesPlayed();
    }
	if( playerNode->getFather()->getFather()){
	playerNode->treeContraction();
    }
    return playerNode->getGamesPlayed() + playerNode->getFather()->getGamesPlayed();
}



//Team* getTeam(Player* player){
//	NodeInUT* playerNode = player->getNode();
//	if(playerNode->getFather() && playerNode->getFather()->getFather()) playerNode->treeContraction();
//    if(playerNode->getFather()) {
//        return playerNode->getFather()->getTeam();
//    }
//    return playerNode->getTeam();
//}


StatusType world_cup_t::add_player_cards(int playerId, int cards) {

    if (playerId <= 0|| cards<0){
        return StatusType::INVALID_INPUT;
    }
    int indexOfPlayer = playersTable.find(playerId);
    if (indexOfPlayer == -1){
        return StatusType::FAILURE;
    }
    Player *player = playersTable.getT(indexOfPlayer);
    NodeInUT *playerNode = player->getNode();
    Team *team;
    if (!playerNode->getFather()) {
        team = playerNode->getTeam();
    }
    else {
        if(playerNode->getFather()->getFather()){
            playerNode->treeContraction();
        }
        team = playerNode->getFather()->getTeam();
    }
     if (!team->isInGame()){
         return StatusType::FAILURE;
     }
    player->addCards(cards);
    team->addCards(cards);
    return StatusType::SUCCESS;
}


output_t<int> world_cup_t::get_player_cards(int playerId){

    if (playerId <= 0) return StatusType::INVALID_INPUT;
    int indexOfPlayer = playersTable.find(playerId);
    if (indexOfPlayer == -1) return StatusType::FAILURE;
    return playersTable.getT(indexOfPlayer)->getCards();
}



output_t<int> world_cup_t::get_team_points(int teamId){
    if(!AVL_team_by_id.find(teamId)) return StatusType::FAILURE;
	return AVL_team_by_id.find(teamId)->data->getPoints();
}


output_t<int> world_cup_t::get_ith_pointless_ability(int i){
    if (!AVL_team_by_id.get_size()||i<0||i>=AVL_team_by_id.get_size()) return StatusType::FAILURE;
    return AVL_team_by_ability.select(i)->data->getId();
}


output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId){
	if (playerId <= 0) return StatusType::INVALID_INPUT;
    int indexOfPlayer = playersTable.find(playerId);
    if (indexOfPlayer == -1) return StatusType::FAILURE;

	NodeInUT* playerNode = playersTable.getT(indexOfPlayer)->getNode();
    NodeInUT* tmpNode = playerNode;
    while (tmpNode->getFather()){
        tmpNode = tmpNode->getFather();
    }
    if (!tmpNode->getTeam()->isInGame()) return StatusType::FAILURE;
    if(!playerNode->getFather()){
        return playerNode->getInternSpirit();
    }
	if(playerNode->getFather()->getFather()){
	playerNode->treeContraction();}
	return playerNode->getFather()->getInternSpirit() * playerNode->getInternSpirit();
}


StatusType world_cup_t::buy_team(int teamId1, int teamId2){

	if (teamId1 <= 0 || teamId2 <= 0 ||teamId1 == teamId2) return StatusType::INVALID_INPUT;
	if(!AVL_team_by_id.find(teamId1)||!AVL_team_by_id.find(teamId2)) return  StatusType::FAILURE;
	Team* team1 = AVL_team_by_id.find(teamId1)->data;
	Team* team2 = AVL_team_by_id.find(teamId2)->data;

    if(team1->getLeader() && team2->getLeader()) {
        NodeInUT* leader1 = team1->getLeader()->getNode();
        NodeInUT* leader2 = team2->getLeader()->getNode();
        if (team1->getNumOfPlayers() < team2->getNumOfPlayers()) {
            leader1->addMatch(-(leader2->getGamesPlayed()));
            permutation_t newSpirit = team1->getTotalSpirit() * leader2->getInternSpirit();
            leader2->setInternSpirit(newSpirit);
            newSpirit = leader2->getInternSpirit().inv() * leader1->getInternSpirit();
            leader1->setInternSpirit(newSpirit);
            leader1->setLeader(leader2);
            team1->setLeader(leader2->getPlayer());
            leader2->setTeam(team1);
        } else {
            leader2->addMatch(-(leader1->getGamesPlayed()));
            permutation_t newSpirit = leader1->getInternSpirit().inv() * team1->getTotalSpirit() * leader2->getInternSpirit();
            leader2->setInternSpirit(newSpirit);
            leader2->setLeader(leader1);
        }
    }
    else if(team2->getLeader()){
        team1->setLeader(team2->getLeader());
        team1->getLeader()->getNode()->setTeam(team1);
    }
	team1->increaseNumOfPlayers(team2->getNumOfPlayers());
	team1->addCards(team2->getTotalCards());
	team1->addGoalKeeper(team2->getNumOfGK());
    AVL_team_by_ability.remove(team1->getAbilityId());
	team1->addAbility(team2->getTotalAbility());
    team1->addSpirit(team2->getTotalSpirit());
    team1->addPoints(team2->getPoints());
    AVL_team_by_ability.insert(team1->getAbilityId(), team1);
    //AVL_team_by_id.find(teamId2)->data->loose();
	AVL_team_by_id.remove(teamId2);
    AVL_team_by_ability.remove(team2->getAbilityId());

	return StatusType::SUCCESS;
}
