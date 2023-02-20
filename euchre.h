#include <vector>
#include "Pack.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <fstream>
#include <istream>


class Game{
    private:
    Pack pack;
    std::vector<Player*> players;
    int leader_index;
    int points_to_win;
    bool shuffling;
    Suit trump;
    Card upcard;
    int points_team1;
    int points_team2;
    int order_up_team;
    std::vector<Player*> original_player_order;
    std::vector<Player*> dealer_order;

    public:
    
    Game(std::vector<Player*> players_in, int pts_to_win, bool shuffle_in, std::istream& pack_name);

    void shuffle();
    void deal();
    void make_trump();
    Card play_card(int index, bool is_leader, Card lead_card);
    std::vector<int> play_hand();
    Player* get_player(int index);
    void player_rotate();
    void play();
    int get_winner(Card card1, Card card2, Card card3, Card card4);
    Suit get_trump();
    bool is_team_1(Player* plyr);

};