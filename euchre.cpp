#include <iostream>
#include "euchre.h"
#include <cassert>

using namespace std;

Game::Game(std::vector<Player*> players_in, int pts_to_win, bool shuffle_in, ifstream& pack_name){
    for(int i = 0; i < players_in.size(); ++i){//in correct order w dealer last at this point
        players.push_back(players_in[i]);
        original_player_order.push_back(players_in[i]);
        dealer_order.push_back(players_in[i]);
    }
    points_to_win = pts_to_win;
    shuffling = shuffle_in;
    pack = Pack(pack_name);
    leader_index = 0;
    points_team1 = 0;
    points_team2 = 0;
    order_up_team = 1;
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
        dealer_order[playercounter]->add_card(pack.deal_one());
    }
    ++playercounter;
    for(int i = 0; i < 2; ++i){//next 2 cards player 2
        dealer_order[playercounter]->add_card(pack.deal_one());
    }
    ++playercounter;
    for(int i = 0; i < 3; ++i){//next 3 cards player 3
        dealer_order[playercounter]->add_card(pack.deal_one());
    }
    ++playercounter; 
    for(int i = 0; i < 2; ++i){//next 2 cards
        dealer_order[playercounter]->add_card(pack.deal_one());
    }
    //next round of dealing
    playercounter = 0;
    for(int i = 0; i < 2; ++i){
        dealer_order[playercounter]->add_card(pack.deal_one());
    }
    ++playercounter;
    for(int i = 0; i < 3; ++i){
        dealer_order[playercounter]->add_card(pack.deal_one());
    }
    ++playercounter;
    for(int i = 0; i < 2; ++i){
        dealer_order[playercounter]->add_card(pack.deal_one());
    }
    ++playercounter;
    for(int i = 0; i < 3; ++i){
        dealer_order[playercounter]->add_card(pack.deal_one());
    }
    upcard = pack.deal_one();
}
void Game::make_trump(){
    bool end_round = false;
    for (int round = 1; round <= 2; round++){
        for (int i = 0; i < 4; i++){
            bool isdealer = false;
            if (i == 3){
                isdealer = true;
            }
            if ((players[i])->make_trump(upcard, isdealer, round, trump)){
                players[i]->add_and_discard(upcard);
                cout << players[i]->get_name() << " orders up " << trump << endl;
                if (i == 1 || i == 3){
                    order_up_team = 1;   
                } else if (i == 2 || i == 4){
                    order_up_team = 2;
                }
                end_round = true;
                break;
            } else {
                cout << players[i]->get_name() << " passes" << endl;
            }
        }
        if (end_round) {
            break;
        }
    }
}

Card Game::play_card(int index, bool is_leader, Card lead_card){
    if (is_leader){
        return players[index]->lead_card(trump);
    }
    return players[index]->play_card(lead_card, trump);
}

vector<int> Game::play_hand(){
    vector<Player*> temp_players;
    vector<int> output;
    int trickcount_team1 = 0;
    int trickcount_team2 = 0;
    for (int i = 0; i < 4; i++){
        temp_players[i] = players[i];
    }
    int winner_index;
    for (int j = 0; j < 5; j++){
        Card rand = Card();//random card for play_card function for leader
        //leader plays card
        int counter = 0;
            Card card_1 = play_card(counter, true, rand);
            cout << card_1 << " led by " << players[0]->get_name();
        counter++;
        //others play cards
            Card card_2 = play_card(counter, false, card_1);
            cout << card_2 << " played by " << players[1]->get_name() << endl;
        counter++;
            Card card_3 = play_card(counter, false, card_1);
            cout << card_3 << " played by " << players[2]->get_name() << endl;
        counter++;
            Card card_4 = play_card(counter, false, card_1);
            cout << card_4 << " played by " << players[3]->get_name() << endl;
        //print winner
        winner_index = get_winner(card_1, card_2, card_3, card_4);
        cout << players[winner_index]->get_name() << " takes the trick\n";
        if(is_team_1(players[winner_index])){//if winner is team 1
            trickcount_team1++;
        }
        else{
            trickcount_team2++;
        }
        //set winner as first index
        
        for(int i = winner_index; i<players.size(); ++i){//winner index onwards
            temp_players[i-winner_index] = players[i];
        }
        for(int i = 0; i < winner_index; ++i){//zero to winner index
            temp_players[winner_index+i] = players[i];
        }
        for(int i = 0; i < players.size(); ++i){//copy temp_players into players
            players[i] = temp_players[i];
        }
    }
    if(trickcount_team1>trickcount_team2){//if team 1 won more tricks
        output.push_back(1);
        output.push_back(trickcount_team1-trickcount_team2);
    }
    else{//if team 2 won more tricks
        output.push_back(2);
        output.push_back(trickcount_team2-trickcount_team1);
    }
    return output;
}
bool Game::is_team_1(Player* plyr){
    if(plyr == original_player_order[0] || plyr == original_player_order[3]){//opposite from original dealer and original dealer
        return true;
    }
    return false;
}

Player* Game::get_player(int index){
    return original_player_order[index];
}

void Game::player_rotate(){
    vector<Player*> temp_players;
    for(int i = 1; i < dealer_order.size(); ++i){
        temp_players.push_back(dealer_order[i]);//every other player except new dealer
    }
    temp_players.push_back(dealer_order[1]);//add dealer to end
    for(int i = 0; i < temp_players.size(); ++i){
        dealer_order[i] = temp_players[i];//copy temp_players into players
    }
}

int Game::get_winner(Card card1, Card card2, Card card3, Card card4){
    if (!Card_less(card1, card2, card1, trump) && !Card_less(card1, card3, card1, trump) 
                        && !Card_less(card1, card4, card1, trump)){
        return 1;
    } else if (!Card_less(card2, card1, card1, trump) && !Card_less(card2, card3, card1, trump) 
                        && !Card_less(card2, card4, card1, trump)){
        return 2;
    } else if (!Card_less(card3, card2, card1, trump) && !Card_less(card3, card1, card1, trump) 
                        && !Card_less(card3, card4, card1, trump)){
        return 3;
    } else if (!Card_less(card4, card2, card1, trump) && !Card_less(card4, card3, card1, trump) 
                        && !Card_less(card4, card1, card1, trump)){
        return 4;
    }
    return -1;  
}

void Game::play(){
    
    pair <Player*, Player*> team_1; 
    team_1.first = original_player_order[3];//initial dealer
    team_1.second = original_player_order[1];//across from dealer

    pair <Player*, Player*> team_2; 
    team_2.first = original_player_order[0];//left of dealer
    team_2.second = original_player_order[2];//right of dealer

    int hand_count = 0;
    while (points_team1 < points_to_win && points_team2 < points_to_win){
        bool plus_two = false;
        cout << "Hand " << hand_count << endl;
        cout << (dealer_order[3])->get_name() << " deals" << endl;
        deal();
        cout << upcard << " turned up" << endl;
        make_trump();
        vector<int> result = play_hand();
        player_rotate();
        if (result[0] == order_up_team && result[1] == 5){
            cout << "march!" << endl;
            plus_two = true;
        } else if (result[0] != order_up_team && result[1] >= 3){
            cout << "euchred!" << endl;
            plus_two = true;
        }
        if (result[0] == 1) {
            cout << (team_1.first)->get_name() << " and " << (team_1.second)->get_name() << " win the hand" << endl;
            if (plus_two){
                points_team1 ++;
            }
            points_team1 ++;
        } else if (result[0] == 2) {
            cout << (team_2.first)->get_name() << " and " << (team_2.second)->get_name() << " win the hand" << endl;
            if (plus_two){
                points_team2 ++;
            }
            points_team2 ++;
        }
    }
    if(points_team1 >= points_to_win){
        cout << (team_1.first)->get_name() << " and " << (team_1.second)->get_name() << " win!" << endl;
    } else if(points_team2 >= points_to_win){
        cout << (team_2.first)->get_name() << " and " << (team_2.second)->get_name() << " win1" << endl;
    }
    for (size_t i = 0; i < players.size(); ++i) {//delete all players
        delete players[i];
    }
    for (size_t i = 0; i < dealer_order.size(); ++i) {
        delete dealer_order[i];
    }
    for (size_t i = 0; i < original_player_order.size(); ++i) {
        delete original_player_order[i];
    }
}

bool is_simple_or_human(string input){
    if (input == "Simple" || input == "Human"){
        return true;
    }
    return false;
}


int main(int argc, char *argv[]){
    //get vector of players, make dealer last index
    
    vector<Player*> temp_players;
    string shuffle = argv[2];
    bool temp_shuffle = (shuffle == "shuffle");
    int points_to_win = atoi(argv[3]);
    if((argc != 12) && (1 <= points_to_win) && (points_to_win <= 100) && ((shuffle == "shuffle") 
        || (shuffle == "noshuffle")) && (is_simple_or_human(argv[5])) && (is_simple_or_human(argv[7]))
        && (is_simple_or_human(argv[9])) && (is_simple_or_human(argv[11]))){//checking for errors in cmd line args
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
    }
    string filename = argv[1];
    ifstream fin(filename);
    if(!fin.is_open()){
        cout << "Error opening " << filename << endl;
        return -1;
    }
    for(int i = 6; i < argc; i+=2){//read in all players, skipping dealer
        temp_players.push_back(Player_factory(argv[i], argv[i+1]));
    }
    temp_players.push_back(Player_factory(argv[4], argv[5]));//add the dealer to the end
    
    Game euchre = Game(temp_players, points_to_win, temp_shuffle, fin);
    for (size_t i = 0; i < temp_players.size(); ++i) {
        delete temp_players[i];
    }
    
    //add playing stuff here
    
    euchre.play();
    
}