#include "worldcup23a2.h"

world_cup_t::world_cup_t(){
}

world_cup_t::~world_cup_t(){
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
    return StatusType::SUCCESS;
}


StatusType world_cup_t::remove_team(int teamId){
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (!AVL_team_by_id.find(teamId)){
        return StatusType::FAILURE;
    }
    Node<int, Team *> *to_delete = AVL_team_by_id.find(teamId);
    if (to_delete){
        AVL_team_by_id.remove(teamId);
        return  StatusType::SUCCESS;
    }
    return StatusType::FAILURE;
}


StatusType world_cup_t::add_player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper){

    if (playerId <= 0 || teamId <= 0 /*|| if spirit not good */ ||gamesPlayed < 0|| cards < 0 ) return StatusType::INVALID_INPUT;
    if (playersTable.find(playerId)!=-1|| AVL_team_by_id.find(teamId)== nullptr) return  StatusType::FAILURE;

	Team* team = AVL_team_by_id.find(teamId)->data;
	Player* newPlayer= new Player(ability, cards, goalKeeper);
	playersTable.insert(playerId, newPlayer);
	team->addSpirit(spirit);
	permutation_t internSpirit = team->getLeader()->getNode()->getInternSpirit().inv()*team->getTotalSpirit();
	int tmpGamesPlayed = gamesPlayed - team->getLeader()->getNode()->getGamesPlayed();
	NodeInUT* newNode = new NodeInUT(playerId, gamesPlayed, internSpirit, newPlayer, team->getLeader()->getNode(), team);
    newPlayer->setNode(newNode);
	team->updateStats(newPlayer, spirit);
    return StatusType::SUCCESS;
}


output_t<int> world_cup_t::play_match(int teamId1, int teamId2){

    if (teamId1 <= 0 || teamId2 <= 0 ||teamId1 == teamId2) return StatusType::INVALID_INPUT;
	if(!AVL_team_by_id.find(teamId1)||!AVL_team_by_id.find(teamId2)) return  StatusType::FAILURE;

	Team* team1 = AVL_team_by_id.find(teamId1)->data;
	Team* team2 = AVL_team_by_id.find(teamId2)->data;
	if(!team1->canPlay()||!team2->canPlay()) return  StatusType::FAILURE;

	team1->getLeader()->getNode()->addMatch();
	team2->getLeader()->getNode()->addMatch();
	Team* winner = nullptr;
	if(team1->getTotalAbility() + team1->getPoints() > team2->getTotalAbility() + team2->getPoints()){
		winner = team1;
	}
	else if(team1->getTotalAbility() + team1->getPoints() < team2->getTotalAbility() + team2->getPoints()){
		winner = team2;
	}
	else if(team1->getTotalAbility() > team2->getTotalAbility()){
		winner = team1;
	}
	else if(team1->getTotalAbility() < team2->getTotalAbility()){
		winner = team2;
	}
	else if(team1->getTotalSpirit().strength() > team2->getTotalSpirit().strength()){
		winner = team1;
	}
	else if(team1->getTotalSpirit().strength() < team2->getTotalSpirit().strength()){
		winner = team2;
	}
	if(winner){
		winner->addPoints(3);
	}
	else{
		team1->addPoints(1);
		team2->addPoints(1);
	}
	return StatusType::SUCCESS;
}


output_t<int> world_cup_t::num_played_games_for_player(int playerId){
    if (playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (playersTable.find(playerId) == -1){
        return StatusType::FAILURE;
    }

    NodeInUT* playerNode = playersTable.getT(playersTable.find(playerId))->getNode();
	if(playerNode->getFather()->getFather()){
	playerNode->treeContraction();}
	int playedGames=0;
	while (playerNode){
		playedGames+=playerNode->getGamesPlayed();
		playerNode = playerNode->getFather();
	}
    return playerNode->getGamesPlayed() + playerNode->getFather()->getGamesPlayed();
}



Team* getTeam(Player* player){	
	NodeInUT* playerNode = player->getNode();
	if(playerNode->getFather() ->getFather()) playerNode->treeContraction();
    return playerNode->getFather()->getTeam();
}


StatusType world_cup_t::add_player_cards(int playerId, int cards){

    if (playerId <= 0) return StatusType::INVALID_INPUT;
    int indexOfPlayer = playersTable.find(playerId);
    if ((indexOfPlayer == -1) || !(playersTable.getT(indexOfPlayer)->getNode()->getTeam()->isInGame())) return StatusType::FAILURE;

    else {
		Player* player = playersTable.getT(indexOfPlayer);
        player->addCards(cards);
        getTeam(player)->addCards(cards);
    }
}


output_t<int> world_cup_t::get_player_cards(int playerId){

    if (playerId <= 0) return StatusType::INVALID_INPUT;
    int indexOfPlayer = playersTable.find(playerId);
    if (indexOfPlayer == -1) return StatusType::FAILURE;
    return playersTable.getT(indexOfPlayer)->getCards();
}



output_t<int> world_cup_t::get_team_points(int teamId){
	return AVL_team_by_id.find(teamId)->data->getPoints();
}


output_t<int> world_cup_t::get_ith_pointless_ability(int i){
	// TODO: Your code goes here
	return 12345;
}


output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId){
	if (playerId <= 0) return StatusType::INVALID_INPUT;
    int indexOfPlayer = playersTable.find(playerId);
    if (indexOfPlayer == -1) return StatusType::FAILURE;

	permutation_t partialSpirit;
	NodeInUT* playerNode = playersTable.getT(indexOfPlayer)->getNode();
	if(playerNode->getFather()->getFather()){
	playerNode->treeContraction();}
	return playerNode->getFather()->getInternSpirit() * playerNode->getInternSpirit();
}


StatusType world_cup_t::buy_team(int teamId1, int teamId2){

	if (teamId1 <= 0 || teamId2 <= 0 ||teamId1 == teamId2) return StatusType::INVALID_INPUT;
	if(!AVL_team_by_id.find(teamId1)||!AVL_team_by_id.find(teamId2)) return  StatusType::FAILURE;
	Team* team1 = AVL_team_by_id.find(teamId1)->data;
	Team* team2 = AVL_team_by_id.find(teamId2)->data;
	NodeInUT* leader1 = team1->getLeader()->getNode();
	NodeInUT* leader2 = team2->getLeader()->getNode();
	if(team1->getNumOfPlayers() < team2->getNumOfPlayers()){
		leader1->addMatch(-(leader2->getGamesPlayed()));
		permutation_t newSpirit = team1->getTotalSpirit() * leader2->getInternSpirit();
		leader2->setInternSpirit(newSpirit);
		newSpirit = leader2->getInternSpirit().inv() * leader1->getInternSpirit();
		leader1->setInternSpirit(newSpirit);
		leader1->setLeader(leader2);
	}
	else{
		leader2->addMatch(-(leader1->getGamesPlayed()));
		permutation_t newSpirit = team1->getTotalSpirit() * leader2->getInternSpirit();
		leader2->setInternSpirit(newSpirit);
		leader2->setLeader(leader1);
	}
	team1->increaseNumOfPlayers(team2->getNumOfPlayers());
	team1->addCards(team2->getTotalCards());
	team1->addGoalKeeper(team2->getNumOfGK());
	team1->addAbility(team2->getTotalAbility());
	AVL_team_by_id.remove(teamId2);
	delete team2;	
	return StatusType::SUCCESS;
}
