#include <iostream>
#include "euchre.h"
#include <fstream>
#include <cassert>

using namespace std;

Game::Game(std::vector<Player*> players_in, int pts_to_win, bool shuffle_in){
    for(int i = 0; i < players_in.size(); ++i){
        players[i] == players_in[i];
    }
    points_to_win = pts_to_win;
    shuffling = shuffle_in;
}
void Game::shuffle(){
    pack.shuffle();
}
void Game::deal(){
    if(shuffling){//shuffle at the start of each deal
        shuffle();
    }
    int playercounter = 0;//start at one to get player 
    for(int i = 0; i < 3; ++i){//first 3 cards player left of dealer
        players[playercounter]->add_card(pack.deal_one());
    }
    ++playercounter;
    for(int i = 0; i < 2; ++i){//next 2 cards player 2
        players[playercounter]->add_card(pack.deal_one());
    }
    ++playercounter;
    for(int i = 0; i < 3; ++i){//next 3 cards player 3
        players[playercounter]->add_card(pack.deal_one());
    }
    ++playercounter; 
    for(int i = 0; i < 2; ++i){//next 2 cards
        players[playercounter]->add_card(pack.deal_one());
    }
    //next round of dealing
    playercounter = 0;
    for(int i = 0; i < 2; ++i){
        players[playercounter]->add_card(pack.deal_one());
    }
    ++playercounter;
    for(int i = 0; i < 3; ++i){
        players[playercounter]->add_card(pack.deal_one());
    }
    ++playercounter;
    for(int i = 0; i < 2; ++i){
        players[playercounter]->add_card(pack.deal_one());
    }
    ++playercounter;
    for(int i = 0; i < 3; ++i){
        players[playercounter]->add_card(pack.deal_one());
    }
    upcard = pack.deal_one();
}
void Game::make_trump(const Card upcard, Suit &trump){
    bool end_round = false;
    for (int j = 1; j < 3; j++){
        for (int i = 0; i < 4; i++){
            bool isdealer = false;
            if (i == 3){
                isdealer == true;
            }
            if ((players[i])->make_trump(upcard, isdealer, j, trump)){
                end_round = true;
                players[i]->add_and_discard(upcard);
                break;
            }
        }
        if (end_round){
            break;
        }
    }
}
Card Game::play_hand(Player *player, bool is_leader, Suit trump, Card lead_card){
    if (is_leader){
        return player->lead_card(trump);
    }
    return player->play_card(lead_card, trump);
    
}

int main(int argc, char *argv[]){
    //get vector of players, make dealer last index
    assert(argc == 12);
    std::vector<Player*> temp_players;
    bool temp_shuffle;
    
    for(int i = 6; i < argc; i+=2){//read in all players, skipping dealer
        temp_players.push_back(Player_factory(argv[i], argv[i+1]));
    }
    temp_players.push_back(Player_factory(argv[4], argv[5]));//add the dealer to the end
    

}