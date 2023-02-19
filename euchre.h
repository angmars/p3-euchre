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

    public:
    
    Game(std::vector<Player*> players_in, int pts_to_win, bool shuffle_in, istream& pack_name);

    void shuffle();
    void deal();
    void Game::make_trump(const Card upcard, Suit &trump);
    Card play_hand(Player *player, bool is_leader, Suit trump, Card lead_card);

};