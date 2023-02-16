#include<vector>
#include "Pack.h"
#include "Player.h"
#include <iostream>
#include <string>


class Game{
    private:
    Pack pack();
    std::vector<Player*> players;
    int points_to_win;


    public:
    
    Game(std::vector<String> player_names, int pts_to_win, );

    void play();
    void shuffle();
    void deal();
    void make_trump();
    void play_hand();

};