//Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <vector>
#include "Pack.h"
#include "Player.h"
#include <string>
#include <fstream>
#include <istream>
#include <cassert>

using namespace std;

class Game{
    private:
    Pack pack;
    std::vector<Player*> players;
    std::vector<Player*> original_player_order;
    std::vector<Player*> dealer_order;
    int leader_index;
    int points_to_win;
    bool shuffling;
    Suit trump;
    Card upcard;
    int points_team1;
    int points_team2;
    int order_up_team;
    
    public:

    Game(Player* one, Player* two, Player* three, Player* four, 
                int pts_to_win, bool shuffle_in, istream& pack_name){

            players.push_back(two);
            players.push_back(three);
            players.push_back(four);
            players.push_back(one);

            original_player_order.push_back(two);
            original_player_order.push_back(three);
            original_player_order.push_back(four);
            original_player_order.push_back(one);

            dealer_order.push_back(two);
            dealer_order.push_back(three);
            dealer_order.push_back(four);
            dealer_order.push_back(one);

        points_to_win = pts_to_win;
        shuffling = shuffle_in;
        pack = Pack(pack_name);
        leader_index = 0;
        points_team1 = 0;
        points_team2 = 0;
        order_up_team = 1;
    }
    void shuffle(){
        pack.shuffle();
    }
    void deal(){
        if(shuffling){//shuffle at the start of each deal
            shuffle();
        }
        //start at one to get player 
        for(int i = 0; i < 3; ++i){//first 3 cards player left of dealer
            Card card1 = pack.deal_one();
            players[0]->add_card(card1);
        }

        for(int i = 0; i < 2; ++i){//next 2 cards player 2
            Card card2 = pack.deal_one();
            players[1]->add_card(card2);
        }

        for(int i = 0; i < 3; ++i){//next 3 cards player 3
            Card card3 = pack.deal_one();
            players[2]->add_card(card3);
        }

        for(int i = 0; i < 2; ++i){//next 2 cards
            Card card4 = pack.deal_one();
            players[3]->add_card(card4);
        }
        //next round of dealing
        for(int i = 0; i < 2; ++i){
            Card card5 = pack.deal_one();
            players[0]->add_card(card5);
        }

        for(int i = 0; i < 3; ++i){
            Card card6 = pack.deal_one();
            players[1]->add_card(card6);
        }

        for(int i = 0; i < 2; ++i){
            Card card7 = pack.deal_one();
            players[2]->add_card(card7);
        }

        for(int i = 0; i < 3; ++i){
            Card card8 = pack.deal_one();
            players[3]->add_card(card8);
        }
        upcard = pack.deal_one();
        pack.reset();
    }
    void make_trump(){
        bool end_round = false;
        for (int round = 1; round <= 2; round++){
            for (int i = 0; i < 4; i++){
                bool isdealer = false;
                if (i == 3){
                    isdealer = true;
                }
                if ((players[i])->make_trump(upcard, isdealer, round, trump)){
                    if (round == 1) {
                        players[3]->add_and_discard(upcard);
                    }
                    cout << players[i]->get_name() << " orders up " << trump << endl;
                    cout << endl;
                    if (i == 1 || i == 3){
                        order_up_team = 1;   
                    } else if (i == 0 || i == 2){
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

    Card play_one_card(int index, bool is_leader, Card lead_card){
        if (is_leader){
            return players[index]->lead_card(trump);
        }
        return players[index]->play_card(lead_card, trump);
    }

    vector<int> play_hand(){
        vector<int> output;
        int trickcount_team1 = 0;
        int trickcount_team2 = 0;

        for (int j = 0; j < 5; j++){
            int winner_index = 0;
            int winner_index_return = 0;
            Card rand = Card();//random card for play_card function for leader
            //leader plays card
            int counter = 0;
                Card card_1 = play_one_card(counter, true, rand);
                cout << card_1 << " led by " << players[0]->get_name() << endl;
            counter++;
            //others play cards
                Card card_2 = play_one_card(counter, false, card_1);
                cout << card_2 << " played by " << players[1]->get_name() << endl;
            counter++;
                Card card_3 = play_one_card(counter, false, card_1);
                cout << card_3 << " played by " << players[2]->get_name() << endl;
            counter++;
                Card card_4 = play_one_card(counter, false, card_1);
                cout << card_4 << " played by " << players[3]->get_name() << endl;
            //print winner
            winner_index = get_winner(card_1, card_2, card_3, card_4);
            cout << players[winner_index]->get_name() << " takes the trick" << endl;
            cout << endl;
            
            for (int i = 0; i < original_player_order.size(); i++){
                if (original_player_order[i]->get_name() == players[winner_index]->get_name()){
                    winner_index_return = i;
                }
            }
            if(is_team_1(winner_index_return)){//if winner is team 1
                trickcount_team1++;
            }
            else{
                trickcount_team2++;
            }
            //set winner as first index
            change_lead(winner_index);
        }

        if(trickcount_team1>trickcount_team2){//if team 1 won more tricks
            output.push_back(1);
            output.push_back(trickcount_team1);
        }
        else{//if team 2 won more tricks
            output.push_back(2);
            output.push_back(trickcount_team2);
        }
        return output;
    }

    void change_lead(int winner_index){
        vector<Player*> temp_players;
        
        for(int i = winner_index; i < players.size(); ++i){//winner index onwards
            temp_players.push_back(players[i]);
        }
        for(int j = 0; j < winner_index; ++j){//zero to winner index
            temp_players.push_back(players[j]);
        }

        for(int k = 0; k < temp_players.size(); ++k){//copy temp_players into players
            players[k] = temp_players[k];
        }
        for(int l = 0; l < temp_players.size(); l++){
            temp_players.erase(temp_players.begin()+l);
        }
    }


    bool is_team_1(int index){
        if(index == 1 || index == 3){//opposite from original dealer and original dealer
            return true;
        }
        return false;
    }

    void players_rotate(){
        vector<Player*> temp_players;
        for(int i = 1; i < dealer_order.size(); ++i){
            temp_players.push_back(dealer_order[i]);//every other player except new dealer
        }
        temp_players.push_back(dealer_order[1]);//add dealer to end
        for(int i = 0; i < temp_players.size(); ++i){
            dealer_order[i] = temp_players[i];//copy temp_players into players
        }
    }

    void players_reset(){
        for(int i = 0; i < players.size(); ++i){
            players[i] = dealer_order[i];
        }
    }
    
    int get_winner(Card card1, Card card2, Card card3, Card card4){
        if (Card_less(card2, card1, card1, trump) && Card_less(card3, card1, card1, trump) 
                            && Card_less(card4, card1, card1, trump)){
            return 0;
        } else if (Card_less(card1, card2, card1, trump) && Card_less(card3, card2, card1, trump) 
                            && Card_less(card4, card2, card1, trump)){
            return 1;
        } else if (Card_less(card1, card3, card1, trump) && Card_less(card2, card3, card1, trump) 
                            && Card_less(card4, card3, card1, trump)){
            return 2;
        } else if (Card_less(card1, card4, card1, trump) && Card_less(card2, card4, card1, trump) 
                            && Card_less(card3, card4, card1, trump)){
            return 3;
        }
        return -1;  
    }

    void play(){
        
        pair <Player*, Player*> team_1; 
        team_1.first = original_player_order[3];//initial dealer
        team_1.second = original_player_order[1];//across from dealer

        pair <Player*, Player*> team_2; 
        team_2.first = original_player_order[0];//left of dealer
        team_2.second = original_player_order[2];//right of dealer

        int hand_count = 0;
        while (points_team1 < points_to_win && points_team2 < points_to_win){
            bool plus_two = false;
            bool march = false;
            bool euchred = false;
            cout << "Hand " << hand_count << endl;
            cout << dealer_order[3]->get_name() << " deals" << endl;
            deal();
            cout << upcard << " turned up" << endl;
            make_trump();
            vector<int> result = play_hand();
            players_rotate();
            players_reset();

            if (result[0] == order_up_team && result[1] == 5){
                plus_two = true;
                march = true;
            } else if (result[0] != order_up_team && result[1] >= 3){
                plus_two = true;
                euchred = true;
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
            if (march){
                cout << "march!" << endl;
            } else if (euchred){
                cout << "euchred!" << endl;
            }
            cout << (team_1.first)->get_name() << " and " << (team_1.second)->get_name() << " have " << points_team1 << " points" << endl;
            cout << (team_2.first)->get_name() << " and " << (team_2.second)->get_name() << " have " << points_team2 << " points" << endl;
            cout << endl;
            hand_count ++;
        }
        if(points_team1 >= points_to_win){
            cout << (team_1.first)->get_name() << " and " << (team_1.second)->get_name() << " win!" << endl;
        } else if(points_team2 >= points_to_win){
            cout << (team_2.first)->get_name() << " and " << (team_2.second)->get_name() << " win!" << endl;
        }
    }

};
bool is_simple_or_human(string input){
    if (input == "Simple" || input == "Human"){
        return true;
    }
    return false;
}


int main(int argc, char *argv[]){
    //get vector of players, make dealer last index
    for (int i = 0; i < argc; i++){
        cout << argv[i] << " ";
    }
    cout << endl;
    
    string Player1Name = argv[4];
    string Player1Type = argv[5];

    string Player2Name = argv[6];
    string Player2Type = argv[7];

    string Player3Name = argv[8];
    string Player3Type = argv[9];

    string Player4Name = argv[10];
    string Player4Type = argv[11];

    string shuffle = string(argv[2]);
    bool temp_shuffle = (shuffle == "shuffle");
    int points_to_win = atoi(argv[3]);
    if((argc != 12) && (1 <= points_to_win) && (points_to_win <= 100) && ((shuffle == "shuffle") 
        || (shuffle == "noshuffle")) && (is_simple_or_human(argv[5])) && (is_simple_or_human(argv[7]))
        && (is_simple_or_human(argv[9])) && (is_simple_or_human(argv[11]))){//checking for errors in cmd line args
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
    }
    string filename = string(argv[1]);
    ifstream fin(filename);
    if(!fin.is_open()){
        cout << "Error opening " << filename << endl;
        return -1;
    }

    Player* one = Player_factory(Player1Name, Player1Type); 
    Player* two = Player_factory(Player2Name, Player2Type); 
    Player* three = Player_factory(Player3Name, Player3Type); 
    Player* four = Player_factory(Player4Name, Player4Type); 

    Game euchre = Game(one, two, three, four, points_to_win, temp_shuffle, fin);
    
    euchre.play();

    delete one;
    delete two;
    delete three;
    delete four;
    
}