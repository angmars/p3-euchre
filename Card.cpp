// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <array>
#include "Card.h"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  is >> str;
  rank = string_to_rank(str);
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  is >> str;
  suit = string_to_suit(str);
  return is;
}


/////////////// Write your implementation for Card below ///////////////


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:


//EFFECTS Initializes Card to the Two of Spades
Card::Card(){
  suit = static_cast<Suit>(0);
  rank = static_cast<Rank>(0);
}

//EFFECTS Initializes Card to specified rank and suit
Card::Card(Rank rank_in, Suit suit_in){

  // Sets the rank and suit with the given rank_in and suit_in
  rank = rank_in;
  suit = suit_in;

}

//EFFECTS Returns the rank
Rank Card::get_rank() const{

  // Returns the rank of a card
  return rank;
}

//EFFECTS Returns the suit.  Does not consider trump.
Suit Card::get_suit() const{

  // Returns the suit without considering the trump suit
  return suit;
}

//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
Suit Card::get_suit(Suit trump) const{

  // Returns either the trump if left bower or the suit
  if (is_left_bower(trump)){
    return trump;
  }
  return suit;
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face_or_ace() const{
  
  // If the value of the suit is greater than 10, (face cards) then return true
  if (suit > static_cast<Suit>(10)) {
    return true;
  }
  return false;
}

//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(Suit trump) const{
  
  // Returns true if the suit equals the trump and is a jack (right bower)
  // Otherwise return false
  if (suit == trump && rank == 11){
    return true;
  }
  return false;
}

//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(Suit trump) const{

  // If trump is one suit, then the opposite color suit is also trump

  // Returns either true if it's the left bower and it's a Jack
  Suit left_bower_suit = Suit_next(trump);
  if (suit == left_bower_suit && rank == 11) {
    return true;
  }
  return false;
}

//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(Suit trump) const {

  // Returns true 
  if (is_left_bower(trump)){
    return true;
  } else if (suit == trump){
    return true;
  }
  return false;
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card){
  os << card.get_rank() << " of " << card.get_suit();
  return os;
}

//EFFECTS Reads a Card from a stream in the format "Two of Spades"
//NOTE The Card class declares this operator>> "friend" function,
//     which means it is allowed to access card.rank and card.suit.
std::istream & operator>>(std::istream &is, Card &card){
  Rank rank_str;
  string of;
  Suit suit_str;
  is >> rank_str >> of >> suit_str;
  card.rank = rank_str;
  card.suit = suit_str;
  return is;
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs){
  return lhs.get_rank() < rhs.get_rank();
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs){
  return lhs.get_rank() <= rhs.get_rank();
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs){
  return lhs.get_rank() > rhs.get_rank();
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs){
  return lhs.get_rank() >= rhs.get_rank();
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs){
  return lhs.get_rank() == rhs.get_rank();
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs){
  return lhs.get_rank() != rhs.get_rank();
}

//EFFECTS returns the next suit, which is the suit of the same color
Suit Suit_next(Suit suit){
  int suit_value = suit;
  if (suit_value <= 1){
    return static_cast<Suit>(suit_value+2);
  } else if (suit_value > 1){
    return static_cast<Suit>(suit_value-2);
  }
  return suit;
}

//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, Suit trump){
  if (b.is_right_bower(trump)){
    return true;
  } else if (a.is_right_bower(trump)){
    return false;
  } else if (b.is_left_bower(trump) && !a.is_right_bower(trump)){
    return true;
  } else if (a.is_left_bower(trump) && !b.is_right_bower(trump)){
    return false;
  } else if (b.is_trump(trump)){
    return true;
  } else if (a.is_trump(trump)){
    return false;
  }
  return (a < b);
}

//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump){
  if (b.is_right_bower(trump)){
    return true;
  } else if (a.is_right_bower(trump)){
    return false;
  } else if (b.is_left_bower(trump) && !a.is_right_bower(trump)){
    return true;
  } else if (a.is_left_bower(trump) && !b.is_right_bower(trump)){
    return false;
  } else if (b.is_trump(trump)){
    return true;
  } else if (a.is_trump(trump)){
    return false;
  } else if (b.get_suit() == led_card.get_suit() && a.get_suit() == led_card.get_suit()){
    return (a < b);
    return true;
  } else if (b.get_suit() == led_card.get_suit()){
    return true;
  } else if (a.get_suit() == led_card.get_suit()){
    return false;
  } 
  return (a < b);
}