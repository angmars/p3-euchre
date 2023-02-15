// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include "Pack.h"
#include "Card.h"

using namespace std;

Player * Player_factory(const std::string &name, const std::string &strategy){
  
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  else if(strategy == "Human"){
    return new HumanPlayer(name);
  }
  assert(false);
  return nullptr;
}
//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p){
os << p.get_name();
}

class SimplePlayer :: public Player{
    private:
    vector<Card> hand;
    int round = 1;
    public:
//EFFECTS returns player's name
const std::string & get_name() const{
    string name;
    cin >> name;
    return name;
}

//REQUIRES player has less than MAX_HAND_SIZE cards
//EFFECTS  adds Card c to Player's hand
void add_card(const Card &c){
    hand.push_back(*c);
}

//REQUIRES round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If Player wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If Player wishes to pass, then do
//  not modify order_up_suit and return false.
bool make_trump(const Card &upcard, bool is_dealer,
                        int round, Suit &order_up_suit) const{
    
    assert(round == 1 || round == 2);

    if (round == 1) {
        
    }
       
}

//REQUIRES Player has at least one card
//EFFECTS  Player adds one card to hand and removes one card from hand.
void add_and_discard(const Card &upcard) = 0;

//REQUIRES Player has at least one card
//EFFECTS  Leads one Card from Player's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
Card lead_card(Suit trump) = 0;

//REQUIRES Player has at least one card
//EFFECTS  Plays one Card from Player's hand according to their strategy.
//  The card is removed from the player's hand.
Card play_card(const Card &led_card, Suit trump) = 0;
}