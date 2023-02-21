// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include <iostream>
#include <cassert>
#include <string>
#include "Card.h"
#include <vector>
#include <algorithm>

using namespace std;

// Simple Player is a class that derives from our Player abstract base class
class SimplePlayer: public Player {

 public:

  SimplePlayer(const std::string &name_in)
    : name(name_in) {  }

  //EFFECTS returns player's name
  const std::string & get_name() const override {

    return name;

  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c) override {

    if (hand.size() < MAX_HAND_SIZE) {
      hand.push_back(c);
    }

  }

  //REQUIRES round is 1 or 2 AND that hand has 5 full cards!!!
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer, int round,
  Suit &order_up_suit) const override {

    assert(round == 1 || round == 2);
    assert(hand.size() == MAX_HAND_SIZE);

    // Find the suit of the upcard and the same colored suit
    const Suit upcard_suit = upcard.get_suit();
    const Suit other_suit = Suit_next(upcard_suit);

    if (round == 1) {

      // Find out how many face/ace cards the player has in trump suit
      int face_ace_trump_counter = 0;
      for (int i=0; i<MAX_HAND_SIZE; ++i) {
        Card shrek = hand.at(i);
        if (shrek.is_face_or_ace() == true && shrek.is_trump(upcard_suit) == true) {
          ++face_ace_trump_counter;
        }
      }

      // Order up if the number of face/ace trump cards >=2, otherwise pass
      if (face_ace_trump_counter >= 2) {
        order_up_suit = upcard_suit;
        return true;
      } else { return false; }
    }

    else {

      if (is_dealer == false) {

        // Find out how many face/ace cards the player has in other suit
        int face_ace_other_counter = 0;
        for (int i=0; i<MAX_HAND_SIZE; ++i) {
          Card donkey = hand.at(i);
          if (donkey.is_face_or_ace() == true && donkey.is_trump(other_suit) == true) {
            ++face_ace_other_counter;
          }
        }

        // Order up if the number of face/ace other cards >=1, otherwise pass
        if (face_ace_other_counter >= 1) {
          order_up_suit = other_suit;
          return true;
        } else { return false; }

      } else { // Screw the dealer!
        order_up_suit = other_suit;
        return true;
      }
    }
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) override {

    assert(hand.size() >= 1);
    const int i_miss_engr_101 = hand.size();

    // Find the current trump suit and smallest card in the current hand
    Card smallest_card = hand.at(0);
    const Suit trump_suit = upcard.get_suit();
    for (int i=1; i<hand.size(); ++i) {
      if (Card_less(hand.at(i), smallest_card, trump_suit) == true) {
        smallest_card = hand.at(i);
      }
    }
    // If the upcard is smaller than/equal to the smallest card, then discard the upcard
    // If this is so, it implies that all the cards must be in the trump suit
    if (Card_less(upcard, smallest_card, trump_suit) == true) {
      return;
    } else if (upcard == smallest_card) { return; }

    // If the upcard is larger than this card, then discard this card
    // And then add the upcard to the hand of cards to replace it
    else {
      for (int j=0; j<hand.size(); ++j) {
        if (hand.at(j) == smallest_card) {
          hand.erase(hand.begin() + j);
          hand.push_back(upcard);
          assert(hand.size() == i_miss_engr_101);
          break;
        }
      }
    }
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed from the player's hand.
  Card lead_card(Suit trump) override {

    assert(hand.size() >= 1);
    bool only_trump_cards = true;

    // Check if they only have trump cards
    for (int i=0; i<hand.size(); ++i) {
      if (hand.at(i).is_trump(trump) == false) {only_trump_cards = false;}
    }

    // If they only have trump cards, play the highest trump card
    if (only_trump_cards == true) {
      int index_of_highest_trump = 0;
      Card highest_trump = hand.at(0);
      for (int j=1; j<hand.size(); ++j) {
        if(Card_less(highest_trump, hand.at(j), trump) == true) {
          highest_trump = hand.at(j);
          index_of_highest_trump = j;
        }
      }
      hand.erase(hand.begin() + index_of_highest_trump);
      return highest_trump;
    }
    // If they have trump and non trump, play the highest non trump card
    else {

      int starting_index_of_highest_non_trump = 0;
      for (int k=0; k<hand.size(); ++k) {
        if (hand.at(k).is_trump(trump) == true) {continue;}
        else {starting_index_of_highest_non_trump = k;}
      }
      Card highest_non_trump = hand.at(starting_index_of_highest_non_trump);

      for (int m=0; m<hand.size(); ++m) {
        if (hand.at(m).is_trump(trump) == true) {continue;}
        else {
          if (Card_less(highest_non_trump, hand.at(m), trump) == true) {
            highest_non_trump = hand.at(m);
            starting_index_of_highest_non_trump = m;
          }
        }
      }
      hand.erase(hand.begin() + starting_index_of_highest_non_trump);
      return highest_non_trump;      
    }
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, Suit trump) override {

    assert(hand.size() >= 1);
    const Suit led_suit = led_card.get_suit(trump);

    // Check if the player has any cards of the same suit as the led suit
    bool can_follow_suit = false;
    for (int i=0; i<hand.size(); ++i) {
      Suit current_cards_suit = hand.at(i).get_suit(trump);
      if (current_cards_suit == led_suit) {
        can_follow_suit = true;
        break;
      }
    }

    // If the player can't follow suit, just play the lowest card in their hand
    if (can_follow_suit == false) {
      Card lowest_card = hand.at(0);
      int index_of_lowest_card = 0;
      for (int j=0; j<hand.size(); ++j) {
        if(Card_less(hand.at(j), lowest_card, led_card, trump) == true) {
          lowest_card = hand.at(j);
          index_of_lowest_card = j;
        }
      }
      hand.erase(hand.begin() + index_of_lowest_card);
      return lowest_card;  
    }

    // If the player can follow suit, play the highest card that follows the suit
    else {
      vector<Card> same_suit_cards;
      for (int k=0; k<hand.size(); ++k) {
        if (hand.at(k).get_suit(trump) == led_suit) {
          same_suit_cards.push_back(hand.at(k));
        }
      }

      Card highest_card = same_suit_cards.at(0);
      for (int z=0; z<same_suit_cards.size(); ++z) {
        if(Card_less(highest_card, same_suit_cards.at(z), trump) == true) {
          highest_card = same_suit_cards.at(z);
        }
      }
      for (int b=0; b<hand.size(); ++b) {
        if (highest_card == hand.at(b)) {
          hand.erase(hand.begin() + b);
          break;
        }
      }
      return highest_card;
    }

  }

  // Maximum number of cards in a player's hand
  static const int MAX_HAND_SIZE = 5;

  // Needed to avoid some compiler errors
  ~SimplePlayer() {}

 private:

  vector<Card> hand;
  string name;

};




// Human Player is a class that derives from our Player abstract base class
class HumanPlayer: public Player {

private:
  vector<Card> hand;
  string name;

// private member funciton that prints out  human player’s hand.
void print_hand() const {
  for (size_t i=0; i < hand.size(); ++i)
    cout << "Human player " << name << "'s hand: "
         << "[" << i << "] " << hand[i] << "\n";
}


 public:
HumanPlayer(const std::string &name_in): name(name_in) {}
  //EFFECTS returns player's name
  virtual const std::string & get_name() const override {
return name; 


  }
  
  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c) override {
    // checks if player has less than max number of cards allowed in hand 
    if (hand.size() < MAX_HAND_SIZE) {

    // adds card to player's hand
        hand.push_back(c);
 }

 // provided in spec; ensures hand is always in sorter order 
 sort(hand.begin(), hand.end());

 }


  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer, int round, 
  Suit &order_up_suit) const override {

    assert(round == 1 || round == 2);
      print_hand();

      cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";

      string decision;
      cin >> decision;

      if (decision != "pass") {
        Suit ordered_up = string_to_suit(decision);
        cout << name << " orders up " << ordered_up << endl;
        
        order_up_suit = ordered_up;
        return true;
      }
      else {
        cout << name << " passes" << endl;

        return false;
      }
    }


  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) override {
    

    assert(hand.size() >= 1);
    const int originalSIZE = hand.size();

    sort(hand.begin(), hand.end());
    print_hand();

    cout << "Discard upcard: [-1]\n";
    cout << "Human player " << name << ", please select a card to discard:\n";


    int decision;
    //user enters # of card they want to discard
    cin >> decision;

    if (decision != -1) {
      // removes a card from hand
      for (size_t i=0; i < hand.size(); ++i) {
            if (decision == i) {
              hand.erase((hand.begin() + i));
            }
      }

      hand.push_back(upcard);
        
    }

    
    assert(hand.size() == originalSIZE);
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(Suit trump) override {

      assert(hand.size() >= 1);

      sort(hand.begin(), hand.end());
      print_hand();

      cout << "Human player " << name << ", please select a card:\n";
      
      int decision;
      cin >> decision;

      cout << hand[decision] << " led by " << name << endl;

      Card card = hand.at(decision);
      // card removed from player's hand 
      hand.erase((hand.begin() + decision));

      return card;


  }

  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, Suit trump) override {

    assert(hand.size() >= 1);
    sort(hand.begin(), hand.end());
    print_hand();

    cout << "Human player " << name << ", please select a card:\n";

    int decision;
    cin >> decision;

    Card card = hand.at(decision);
    hand.erase((hand.begin() + decision));

    return card;
 }
  

  // Maximum number of cards in a player's hand
  static const int MAX_HAND_SIZE = 5;

  // Needed to avoid some compiler errors
  ~HumanPlayer() {}


};

// returns a pointer to a Player with the correct dynamic type
Player * Player_factory(const std::string &name, const std::string &strategy) {

  // We need to check the value of strategy and return
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  if (strategy == "Human") {
    return new HumanPlayer(name);
  }
  // Invalid strategy if we get here

  return nullptr;

}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {

  std::string playername = p.get_name();
  os << playername;
  return os;

}
