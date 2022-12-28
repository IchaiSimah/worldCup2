#include "worldcup23a2.h"

world_cup_t::world_cup_t(){
}

world_cup_t::~world_cup_t(){
}

StatusType world_cup_t::add_team(int teamId)
{
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

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper){
    if (playerId <= 0 || teamId <= 0 /*|| if spirit not good */ ||gamesPlayed < 0|| cards < 0 ){
        return StatusType::INVALID_INPUT;
        if (playersTable.find(playerId)!=-1|| AVL_team_by_id.find(teamId)== nullptr) return  StatusType::FAILURE;

        //continuer ici

        return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId){
    if (playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (playersTable.find(playerId) == -1){
        return StatusType::FAILURE;
    }
    Player* player = playersTable.getT(playersTable.find(playerId));
    return player->getNumGames() + player->getTeam()->getGamePlayed();
}

StatusType world_cup_t::add_player_cards(int playerId, int cards){

    if (playerId <= 0)return StatusType::INVALID_INPUT;
    int indexOfPlayer = playersTable.find(playerId);
    if ((indexOfPlayer == -1) || !(playersTable.getT(indexOfPlayer)->getTeam()->isInGame())) return StatusType::FAILURE;
    if (indexOfPlayer != -1){
        playersTable.getT(indexOfPlayer)->addCards(cards);
        playersTable.getT(indexOfPlayer)->getTeam()->addCards(cards);
    }

output_t<int> world_cup_t::get_player_cards(int playerId){

    if (playerId <= 0) return StatusType::INVALID_INPUT;
    int indexOfPlayer = playersTable.find(playerId);
    if ((indexOfPlayer == -1) && !(playersTable.getT(indexOfPlayer)->getTeam()->isInGame())) return StatusType::FAILURE;
    return playersTable.getT(indexOfPlayer)->getCards();
}

return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
