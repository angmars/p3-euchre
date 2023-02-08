// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>
#include <cassert>

using namespace std;


TEST(test_card_ace_heart) {

    // Testing get rank and suit with Card(rank,suit)
    Card c = Card(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_card_default) {

    // Testing get rank and suit with Card()
    Card c = Card();
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}

TEST(test_card_trump_suit_left_bower){

    // Testing that the left bower is considered a trump suit
    Card c = Card(JACK, SPADES);
    ASSERT_EQUAL(CLUBS, c.get_suit(CLUBS));
}

TEST(test_card_is_face){

    // Testing that the Jack is a face card
    Card a = Card(JACK, CLUBS);
    ASSERT_TRUE(a.is_face_or_ace());

    Card b = Card(NINE, CLUBS);
    ASSERT_FALSE(b.is_face_or_ace());

    Card c = Card(ACE, SPADES);
    ASSERT_TRUE(c.is_face_or_ace());
}

TEST(test_card_not_right_bower_rank){

    // Testing that a card is not the right bower despite trump suit
    Card c = Card(KING, HEARTS);
    ASSERT_FALSE(c.is_right_bower(HEARTS));
}

TEST(test_card_not_right_bower_suit){

    // Testing that a card is not the right bower despite rank
    Card c = Card(JACK, SPADES);
    ASSERT_FALSE(c.is_right_bower(HEARTS));
}

TEST(test_card_is_right_bower){

    // Testing that a card is the right bower
    Card c = Card(JACK, SPADES);
    ASSERT_TRUE(c.is_right_bower(SPADES));
}

TEST(test_card_not_right_bower_left_bower){

    // Testing that a card is not the right bower even though it's the left bower
    Card c = Card(JACK, DIAMONDS);
    ASSERT_FALSE(c.is_right_bower(HEARTS));
}

TEST(test_card_not_left_bower_suit){

    // Testing that a card is not the left bower despite suit
    Card c = Card(KING, DIAMONDS);
    ASSERT_FALSE(c.is_left_bower(HEARTS));
}

TEST(test_card_not_left_bower_rank){

    // Testing that a card is not the left bower despite rank
    Card c = Card(JACK, SPADES);
    ASSERT_FALSE(c.is_left_bower(HEARTS));
}

TEST(test_card_is_left_bower){

    // Testing that a card is indeed the left bower
    Card c = Card(JACK, SPADES);
    ASSERT_TRUE(c.is_left_bower(CLUBS));
}

TEST(test_card_not_left_bower_right_bower){

    // Testing that the card is not the left bower despite being the right bower
    Card c = Card(JACK, DIAMONDS);
    ASSERT_FALSE(c.is_left_bower(DIAMONDS));
}

TEST(test_card_is_trump){

    // Testing that the card is a trump
    Card c = Card(THREE, CLUBS);
    ASSERT_TRUE(c.is_trump(CLUBS));
}

TEST(test_card_is_trump_right_bower){

    // Testing that the card is a trump despite being right bower
    Card c = Card(JACK, CLUBS);
    ASSERT_TRUE(c.is_trump(CLUBS));
}

TEST(test_card_is_trump_left_bower){

    // Testing that the card is a trump despite being left bower
    Card c = Card(JACK, SPADES);
    ASSERT_TRUE(c.is_trump(CLUBS));
}

TEST(test_card_not_trump){

    // Testing that the card isn't a trump
    Card c = Card(QUEEN, HEARTS);
    ASSERT_FALSE(c.is_trump(DIAMONDS));
}

TEST(test_card_suit_next){
    
    // Testing the suit next function black
    ASSERT_EQUAL(CLUBS, Suit_next(SPADES));
    ASSERT_EQUAL(SPADES, Suit_next(CLUBS));
    ASSERT_EQUAL(DIAMONDS, Suit_next(HEARTS));
    ASSERT_EQUAL(HEARTS, Suit_next(DIAMONDS));
}

// Testing Card_less without led suit
TEST(test_card_right_bower){

    // Testing that the right bower beats the left bower
    Card a = Card(JACK, DIAMONDS);
    Card b = Card(JACK, HEARTS);
    ASSERT_TRUE(Card_less(a, b, HEARTS));

    Card c = Card(JACK, HEARTS);
    Card d = Card(JACK, DIAMONDS);
    ASSERT_FALSE(Card_less(c, d, HEARTS));
    
    Card e = Card(JACK, SPADES);
    Card f = Card(JACK, SPADES);
    ASSERT_FALSE(Card_less(e, f, SPADES));
}

TEST(test_card_left_bower){

    // Testing that the left bower beats everything else
    Card a = Card(TEN, CLUBS);
    Card b = Card(JACK, CLUBS);
    ASSERT_TRUE(Card_less(a, b, SPADES));

    Card c = Card(JACK, SPADES);
    Card d = Card(QUEEN, SPADES);
    ASSERT_FALSE(Card_less(c, d, CLUBS));
}

TEST(test_card_trump){

    // Testing the card basic versus the trump card same rank
    Card a = Card(NINE, HEARTS);
    Card b = Card(NINE, DIAMONDS);
    ASSERT_TRUE(Card_less(a, b, DIAMONDS));

    Card c = Card(ACE, SPADES);
    Card d = Card(ACE, CLUBS);
    ASSERT_FALSE(Card_less(c, d,  SPADES));

    Card e = Card(NINE, DIAMONDS);
    Card f = Card(ACE, DIAMONDS);
    ASSERT_TRUE(Card_less(e, f, DIAMONDS));

    Card g = Card(NINE, DIAMONDS);
    Card h = Card(TWO, DIAMONDS);
    ASSERT_FALSE(Card_less(g, h, DIAMONDS));

    Card i = Card(TEN, DIAMONDS);
    Card j = Card(TEN, DIAMONDS);
    ASSERT_FALSE(Card_less(i, j, DIAMONDS));
}

TEST(test_card_basic){

    // Testing two basic cards against each other
    Card a = Card(TWO, CLUBS);
    Card b = Card(THREE, SPADES);
    ASSERT_TRUE(Card_less(a, b, HEARTS));

    Card c = Card(FOUR, CLUBS);
    Card d = Card(THREE, DIAMONDS);
    ASSERT_FALSE(Card_less(c, d, SPADES));

    Card e = Card(KING, HEARTS);
    Card f = Card(KING, HEARTS);
    ASSERT_FALSE(Card_less(e, f, DIAMONDS));
}

TEST(test_card_basic_v_basic_same_rank){
    Card a = Card(NINE, SPADES);
    Card b = Card(NINE, HEARTS);
    ASSERT_TRUE(Card_less(a, b, CLUBS));

    Card c = Card(NINE, CLUBS);
    Card d = Card(NINE, DIAMONDS);
    ASSERT_TRUE(Card_less(c, d, SPADES));

    Card e = Card(FIVE, CLUBS);
    Card f = Card(FIVE, SPADES);
    ASSERT_FALSE(Card_less(e, f, DIAMONDS));

    Card g = Card(FIVE, CLUBS);
    Card h = Card(FIVE, CLUBS);
    ASSERT_FALSE(Card_less(g, h, DIAMONDS));
}

// Testing Card_less with led_suit <- same idea as the other Card_less tests
TEST(test_card_right_bower_led){
    Card a = Card(JACK, DIAMONDS);
    Card b = Card(JACK, HEARTS);
    Card led1 = Card(TEN, DIAMONDS);
    ASSERT_TRUE(Card_less(a, b, led1, HEARTS));

    Card c = Card(JACK, HEARTS);
    Card d = Card(JACK, DIAMONDS);
    Card led2 = Card(TEN, DIAMONDS);
    ASSERT_FALSE(Card_less(c, d, led2, HEARTS));

    Card e = Card(JACK, SPADES);
    Card f = Card(JACK, SPADES);
    Card led3 = Card(JACK, CLUBS);
    ASSERT_FALSE(Card_less(e, f, led3, SPADES));
}

TEST(test_card_left_bower_led){
    Card a = Card(TEN, CLUBS);
    Card b = Card(JACK, CLUBS);
    Card led1 = Card(TEN, DIAMONDS);
    ASSERT_TRUE(Card_less(a, b, led1, CLUBS));

    Card c = Card(JACK, SPADES);
    Card d = Card(QUEEN, SPADES);
    Card led2 = Card(TEN, DIAMONDS);
    ASSERT_FALSE(Card_less(c, d, led2, SPADES));
}

TEST(test_card_trump_led){
    Card a = Card(NINE, DIAMONDS);
    Card b = Card(ACE, DIAMONDS);
    Card led1 = Card(TEN, SPADES);
    ASSERT_TRUE(Card_less(a, b, led1, DIAMONDS));

    Card c = Card(NINE, DIAMONDS);
    Card d = Card(TWO, DIAMONDS);
    Card led2 = Card(TEN, SPADES);
    ASSERT_FALSE(Card_less(c, d, led2, DIAMONDS));

    Card e = Card(TEN, DIAMONDS);
    Card f = Card(TEN, DIAMONDS);
    Card led3 = Card(NINE, SPADES);
    ASSERT_FALSE(Card_less(e, f, led3, DIAMONDS));

    Card g = Card(NINE, HEARTS);
    Card h = Card(NINE, DIAMONDS);
    Card led4 = Card(TEN, HEARTS);
    ASSERT_TRUE(Card_less(g, h, led4, DIAMONDS));

    Card i = Card(ACE, SPADES);
    Card j = Card(ACE, CLUBS);
    Card led5 = Card(TEN, CLUBS);
    ASSERT_FALSE(Card_less(i, j, led5, SPADES));
}

TEST(test_card_led){
    
    // Testing the led card against a led card true
    Card a = Card(TWO, DIAMONDS);
    Card b = Card(ACE, DIAMONDS);
    Card led1 = Card(TEN, DIAMONDS);
    ASSERT_TRUE(Card_less(a, b, led1, SPADES));

    Card c = Card(ACE, DIAMONDS);
    Card d = Card(FOUR, DIAMONDS);
    Card led2 = Card(TEN, DIAMONDS);
    ASSERT_FALSE(Card_less(c, d, led2, SPADES));

    Card e = Card(TEN, DIAMONDS);
    Card f = Card(TEN, DIAMONDS);
    Card led3 = Card(JACK, DIAMONDS);
    ASSERT_FALSE(Card_less(e, f, led3, SPADES));

    Card g = Card(ACE, SPADES);
    Card h = Card(ACE, CLUBS);
    Card led4 = Card(TEN, CLUBS);
    ASSERT_TRUE(Card_less(g, h, led4, HEARTS));

    Card i = Card(ACE, SPADES);
    Card j = Card(ACE, CLUBS);
    Card led5 = Card(TEN, SPADES);
    ASSERT_FALSE(Card_less(i, j, led5, HEARTS));
}

TEST(test_card_basic_led){
    Card a = Card(TWO, CLUBS);
    Card b = Card(THREE, SPADES);
    Card led1 = Card(TEN, HEARTS);
    ASSERT_TRUE(Card_less(a, b, led1, HEARTS));

    Card c = Card(FOUR, CLUBS);
    Card d = Card(THREE, DIAMONDS);
    Card led2 = Card(TEN, SPADES);
    ASSERT_FALSE(Card_less(c, d, led2, SPADES));

    Card e = Card(KING, HEARTS);
    Card f = Card(KING, HEARTS);
    Card led3 = Card(TEN, SPADES);
    ASSERT_FALSE(Card_less(e, f, led3, DIAMONDS));
}

TEST(test_card_basic_v_basic_same_rank_led){
    Card a = Card(NINE, SPADES);
    Card b = Card(NINE, HEARTS);
    Card led1 = Card(JACK, CLUBS);
    ASSERT_TRUE(Card_less(a, b, led1, CLUBS));

    Card c = Card(NINE, CLUBS);
    Card d = Card(NINE, DIAMONDS);
    Card led2 = Card(JACK, SPADES);
    ASSERT_TRUE(Card_less(c, d, led2, SPADES));

    Card e = Card(FIVE, CLUBS);
    Card f = Card(FIVE, SPADES);
    Card led3 = Card(JACK, DIAMONDS);
    ASSERT_FALSE(Card_less(e, f, led3, DIAMONDS));

    Card g = Card(FIVE, CLUBS);
    Card h = Card(FIVE, CLUBS);
    Card led4 = Card(JACK, DIAMONDS);
    ASSERT_FALSE(Card_less(g, h, led4, DIAMONDS));
}

// Operator tests
TEST(test_card_operator_less_than_true){
    Card a = Card(EIGHT, SPADES);
    Card b = Card(NINE, HEARTS);
    ASSERT_TRUE(a<b);
}

TEST(test_card_operator_less_than_false){
    Card a = Card(ACE, SPADES);
    Card b = Card(NINE, HEARTS);
    ASSERT_FALSE(a<b);
}

TEST(test_card_operator_less_than_equal_true){
    Card a = Card(EIGHT, SPADES);
    Card b = Card(EIGHT, DIAMONDS);
    ASSERT_TRUE(a<b);
}

TEST(test_card_operator_less_than_equal_false){
    Card a = Card(EIGHT, CLUBS);
    Card b = Card(EIGHT, HEARTS);
    ASSERT_FALSE(a<b);
}

TEST(test_card_operator_less_than_or_equal_to_true1){
    Card a = Card(SEVEN, SPADES);
    Card b = Card(NINE, HEARTS);
    ASSERT_TRUE(a<=b);
}

TEST(test_card_operator_less_than_or_equal_to_true2){
    Card a = Card(SEVEN, SPADES);
    Card b = Card(SEVEN, SPADES);
    ASSERT_TRUE(a<=b);
}

TEST(test_card_operator_less_than_or_equal_true3){
    Card a = Card(SEVEN, SPADES);
    Card b = Card(SEVEN, DIAMONDS);
    ASSERT_TRUE(a<=b);
}

TEST(test_card_operator_less_than_or_equal_to_false1){
    Card a = Card(KING, SPADES);
    Card b = Card(NINE, HEARTS);
    ASSERT_FALSE(a<=b);
}

TEST(test_card_operator_less_than_or_equal_false2){
    Card a = Card(SEVEN, CLUBS);
    Card b = Card(SEVEN, HEARTS);
    ASSERT_FALSE(a<=b);
}

TEST(test_card_operator_greater_than_true){
    Card a = Card(QUEEN, SPADES);
    Card b = Card(NINE, HEARTS);
    ASSERT_TRUE(a>b);
}

TEST(test_card_operator_greater_than_false1){
    Card a = Card(QUEEN, SPADES);
    Card b = Card(KING, HEARTS);
    ASSERT_FALSE(a>b);
}

TEST(test_card_operator_greater_than_false2){
    Card a = Card(KING, SPADES);
    Card b = Card(KING, HEARTS);
    ASSERT_FALSE(a>b);
}

TEST(test_card_operator_greater_than_or_equal_to_true1){
    Card a = Card(ACE, SPADES);
    Card b = Card(KING, HEARTS);
    ASSERT_TRUE(a>=b);
}

TEST(test_card_operator_greater_than_or_equal_to_true2){
    Card a = Card(ACE, DIAMONDS);
    Card b = Card(ACE, HEARTS);
    ASSERT_TRUE(a>=b);
}

TEST(test_card_operator_equal_to_true){
    Card a = Card(FIVE, HEARTS);
    Card b = Card(FIVE, HEARTS);
    ASSERT_TRUE(a==b);
}

TEST(test_card_operator_equal_to_false1){
    Card a = Card(ACE, SPADES);
    Card b = Card(TWO, HEARTS);
    ASSERT_FALSE(a==b);
}

TEST(test_card_operator_equal_to_false2){
    Card a = Card(SEVEN, DIAMONDS);
    Card b = Card(SEVEN, CLUBS);
    ASSERT_FALSE(a==b);
}

TEST(test_card_operator_not_equal_to_true1){
    Card a = Card(ACE, SPADES);
    Card b = Card(KING, HEARTS);
    ASSERT_TRUE(a!=b);
}

TEST(test_card_operator_not_equal_true2){
    Card a = Card(NINE, SPADES);
    Card b = Card(KING, HEARTS);
    ASSERT_TRUE(a!=b);
}

TEST(test_card_operator_not_equal_true3){
    Card a = Card(NINE, SPADES);
    Card b = Card(NINE, HEARTS);
    ASSERT_TRUE(a!=b);
}

TEST(test_card_operator_not_equal_false){
    Card a = Card(TWO, SPADES);
    Card b = Card(TWO, SPADES);
    ASSERT_FALSE(a!=b);
}
// Add more test cases here
    
TEST_MAIN()
