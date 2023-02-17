// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include "Player.h"
#include <cassert>
#include <algorithm>

using namespace std;


class SimplePlayer : public Player {
    private:
    vector<Card> hand;
    string player_name;
  public:

  SimplePlayer(string name){
    player_name = name;
  }
  //EFFECTS returns player's name
  const std::string & get_name() const{
      return player_name;
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c){
      assert(hand.size() < MAX_HAND_SIZE);
      hand.push_back(c);
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
      int counter1 = 0;
      for (int i = 0; i < hand.size(); i++){ 
        if ((hand[i].is_face_or_ace() && hand[i].is_trump(upcard.get_suit())) || 
            hand[i].is_left_bower(upcard.get_suit()) || 
            hand[i].is_right_bower(upcard.get_suit())){
          counter1 ++;
        }
      }
      if (counter1 >= 2){
        order_up_suit = upcard.get_suit();
        return true;
      } else {
        return false;
      }  
    } else if (round == 2){
      int counter2 = 0;
      for (int j = 0; j < hand.size(); j++){
        if ((hand[j].is_face_or_ace() && hand[j].is_trump(Suit_next(upcard.get_suit()))) || 
            hand[j].is_left_bower(Suit_next(upcard.get_suit())) || 
            hand[j].is_right_bower(Suit_next(upcard.get_suit()))){
          counter2 ++;
        }
      }
    if (counter2 >= 1 || is_dealer) {
      order_up_suit = Suit_next(upcard.get_suit());
      return true;
    } else {
      return false;
    }
  }
  return false;
}

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard){

    assert(hand.size() >= 1);

    int index = 0;
    Card discard = Card(JACK, upcard.get_suit());
    for (int i = 0; i < hand.size(); i++){
      if (Card_less(hand[i], discard, upcard.get_suit())){
        discard = hand[i];
        index = i;
      }
    }
    hand[index] = upcard;
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(Suit trump) {
    assert(hand.size() >= 1);

    Card highbasic = Card(TWO, Suit_next(trump));
    Card hightrump = Card(TWO, trump);
    int indexbasic = 0;
    int indextrump = 0;
    int trumpcount = 0;

    for (int i = 0; i < hand.size(); i++){
      if (!hand[i].is_trump(trump)){
        if (Card_less(highbasic, hand[i], trump)){
          highbasic = hand[i];
          indexbasic = i;
        }
      } else {
        trumpcount ++;
        if (Card_less(hightrump, hand[i], trump)){
          hightrump = hand[i];
          indextrump = i;
        }
      }
    }
    if (trumpcount == hand.size()){
      hand.erase(hand.begin()+indextrump);
      return hightrump;
    }
    hand.erase(hand.begin()+indexbasic);
    return highbasic;
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, Suit trump) {
    assert(hand.size() >= 1);

    Card highled = Card(TWO, led_card.get_suit());
    Card lowbasic = Card(JACK, trump);
    int indexled = 0;
    int indexbasic = 0;
    int ledcount = 0;

    for (int i = 0; i < hand.size(); i++){
      if ((hand[i].get_suit(trump) == led_card.get_suit(trump))) {
        ledcount ++;
        if (Card_less(highled, hand[i], trump)){
          highled = hand[i];
          indexled = i;
        }
      } else {
        if (Card_less(hand[i], lowbasic, trump)){
          lowbasic = hand[i];
          indexbasic = i;
        }
      }
    }
    if (ledcount >= 1){
      hand.erase(hand.begin()+indexled);
      return highled;
    }
    hand.erase(hand.begin()+indexbasic);
    return lowbasic;
  }
};

class HumanPlayer : public Player {
    private:
    vector<Card> hand;
    string player_name;
  public:
  
  HumanPlayer(string name){
    player_name = name;
  }
  //Prints hand
  void print_hand() const {
  for (size_t i=0; i < hand.size(); ++i)
    cout << "Human player " << player_name << "'s hand: "
         << "[" << i << "] " << hand[i] << "\n";
}
  //EFFECTS returns player's name
  const std::string & get_name() const{
      return player_name;
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c){
    assert(hand.size() < MAX_HAND_SIZE);
      hand.push_back(c);
      sort(hand.begin(), hand.end());
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) const{//do we need all these parameters?
      string decision;
      assert(round == 1 || round == 2);
      print_hand();
      cout << "Human player " << player_name << ", please enter a suit, or \"pass\":\n";
      cin >> decision;

    if(decision != "pass") {
    order_up_suit = string_to_suit(decision);
    }
    return false;
                          }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) {
    assert(hand.size() >= 1);
    int discard;
    print_hand();
    cout << "Discard upcard: [-1]\n";
    cout << "Human player " << player_name << ", please select a card to discard:\n";
    cin >> discard;
    if(discard != -1){//if player wants to discard non-upcard
      hand.erase(hand.begin()+discard);//discard
      add_card(upcard);//add upcard
    }
  }
  Card lead_card(Suit trump){
      Card blah = Card();
      Card played = play_card(blah, trump);
      return played;
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, Suit trump) {
    assert(hand.size() >= 1);
    print_hand();
    int selected_card;
    cout << "Human player " << player_name << ", please select a card:\n";
    cin >> selected_card;
    Card tempcard = hand[selected_card];//make tempcard to return
    hand.erase(hand.begin() + selected_card);//discard card from hand
    return tempcard;
  }
};

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
  return os;
}