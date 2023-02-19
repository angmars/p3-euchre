#include <vector>
#include "Pack.h"
#include "Player.h"
#include <iostream>
#include <string>


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

    public:
    
    Game(std::vector<Player*> players_in, int pts_to_win, bool shuffle_in, istream& pack_name);

    void shuffle();
    void deal();
    void Game::make_trump();
    Card play_card(int index, bool is_leader, Card lead_card);
    vector<int> Game::play_hand();
    Player* Game::get_player(int index);
    void Game::player_rotate();
    void Game::play();
    int Game::get_winner(Card card1, Card card2, Card card3, Card card4);
    Suit Game::get_trump();
    bool Game::is_team_1(Player* plyr);

};