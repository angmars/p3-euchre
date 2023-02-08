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

TEST(test_card_not_face){

    // Testing that the value of nine is not a face card
    Card c = Card(NINE, CLUBS);
    ASSERT_EQUAL(false, c.is_face_or_ace());
}

TEST(test_card_is_face){

    // Testing that the Jack is a face card
    Card c = Card(JACK, CLUBS);
    ASSERT_EQUAL(true, c.is_face_or_ace());
}

TEST(test_card_is_ace){

    // Testing that the ace is considered a face
    Card c = Card(ACE, SPADES);
    ASSERT_EQUAL(true, c.is_face_or_ace());
}

TEST(test_card_not_right_bower_rank){

    // Testing that a card is not the right bower despite trump suit
    Card c = Card(KING, HEARTS);
    ASSERT_EQUAL(false, c.is_right_bower(HEARTS));
}

TEST(test_card_not_right_bower_suit){

    // Testing that a card is not the right bower despite rank
    Card c = Card(JACK, SPADES);
    ASSERT_EQUAL(false, c.is_right_bower(HEARTS));
}

TEST(test_card_is_right_bower){

    // Testing that a card is the right bower
    Card c = Card(JACK, SPADES);
    ASSERT_EQUAL(true, c.is_right_bower(SPADES));
}

TEST(test_card_not_right_bower_left_bower){

    // Testing that a card is not the right bower even though it's the left bower
    Card c = Card(JACK, DIAMONDS);
    ASSERT_EQUAL(false, c.is_right_bower(HEARTS));
}

TEST(test_card_not_left_bower_suit){

    // Testing that a card is not the left bower despite suit
    Card c = Card(KING, DIAMONDS);
    ASSERT_EQUAL(false, c.is_left_bower(HEARTS));
}

TEST(test_card_not_left_bower_rank){

    // Testing that a card is not the left bower despite rank
    Card c = Card(JACK, SPADES);
    ASSERT_EQUAL(false, c.is_left_bower(HEARTS));
}

TEST(test_card_is_left_bower){

    // Testing that a card is indeed the left bower
    Card c = Card(JACK, SPADES);
    ASSERT_EQUAL(true, c.is_left_bower(CLUBS));
}

TEST(test_card_not_left_bower_right_bower){

    // Testing that the card is not the left bower despite being the right bower
    Card c = Card(JACK, DIAMONDS);
    ASSERT_EQUAL(false, c.is_left_bower(DIAMONDS));
}

TEST(test_card_is_trump){

    // Testing that the card is a trump
    Card c = Card(THREE, CLUBS);
    ASSERT_EQUAL(true, c.is_trump(CLUBS));
}

TEST(test_card_is_trump_right_bower){

    // Testing that the card is a trump despite being right bower
    Card c = Card(JACK, CLUBS);
    ASSERT_EQUAL(true, c.is_trump(CLUBS));
}

TEST(test_card_is_trump_left_bower){

    // Testing that the card is a trump despite being left bower
    Card c = Card(JACK, SPADES);
    ASSERT_EQUAL(true, c.is_trump(CLUBS));
}

TEST(test_card_not_trump){

    // Testing that the card isn't a trump
    Card c = Card(QUEEN, HEARTS);
    ASSERT_EQUAL(false, c.is_trump(DIAMONDS));
}

TEST(test_card_suit_next1){
    
    // Testing the suit next function black
    ASSERT_EQUAL(CLUBS, Suit_next(SPADES));
    ASSERT_EQUAL(SPADES, Suit_next(CLUBS));
}

TEST(test_card_suit_next2){
    
    // Testing the suit next function red
    ASSERT_EQUAL(DIAMONDS, Suit_next(HEARTS));
    ASSERT_EQUAL(HEARTS, Suit_next(DIAMONDS));
}

// Testing Card_less without led suit
TEST(test_card_left_bower_v_right_bower){

    // Testing that the right bower beats the left bower
    Card a = Card(JACK, DIAMONDS);
    Card b = Card(JACK, HEARTS);
    ASSERT_EQUAL(true, Card_less(a, b, HEARTS));
}

TEST(test_card_right_bower_v_left_bower){

    // Testing the flip side
    Card a = Card(JACK, HEARTS);
    Card b = Card(JACK, DIAMONDS);
    ASSERT_EQUAL(false, Card_less(a, b, HEARTS));
}

TEST(test_card_right_bower_v_right_bower){

    // Testing the right bower against the right bower
    Card a = Card(JACK, SPADES);
    Card b = Card(JACK, SPADES);
    ASSERT_EQUAL(false, Card_less(a, b, SPADES));
}

TEST(test_card_trump_v_left_bower){

    // Testing that the left bower beats everything else
    Card a = Card(TEN, CLUBS);
    Card b = Card(JACK, CLUBS);
    ASSERT_EQUAL(true, Card_less(a, b, CLUBS));
}

TEST(test_card_left_bower_v_trump){

    // Testing the flip side
    Card a = Card(JACK, SPADES);
    Card b = Card(QUEEN, SPADES);
    ASSERT_EQUAL(false, Card_less(a, b, SPADES));
}

TEST(test_card_basic_v_trump){

    // Testing the card basic versus the trump card same rank
    Card a = Card(NINE, HEARTS);
    Card b = Card(NINE, DIAMONDS);
    ASSERT_EQUAL(true, Card_less(a, b, DIAMONDS));
}

TEST(test_card_trump_v_basic){

    // Testing the flip side (same rank)
    Card a = Card(ACE, SPADES);
    Card b = Card(ACE, CLUBS);
    ASSERT_EQUAL(false, Card_less(a, b,  SPADES));
}

TEST(test_card_trump_v_trump_true){
    Card a = Card(NINE, DIAMONDS);
    Card b = Card(ACE, DIAMONDS);
    ASSERT_EQUAL(true, Card_less(a, b, DIAMONDS));
}

TEST(test_card_trump_v_trump_false1){
    Card a = Card(NINE, DIAMONDS);
    Card b = Card(TWO, DIAMONDS);
    ASSERT_EQUAL(false, Card_less(a, b, DIAMONDS));
}

TEST(test_card_trump_v_trump_false2){
    Card a = Card(TEN, DIAMONDS);
    Card b = Card(TEN, DIAMONDS);
    ASSERT_EQUAL(false, Card_less(a, b, DIAMONDS));
}

TEST(test_card_basic_v_basic_true){

    // Testing two basic cards against each other
    Card a = Card(TWO, CLUBS);
    Card b = Card(THREE, SPADES);
    ASSERT_EQUAL(true, Card_less(a, b, HEARTS));
}

TEST(test_card_basic_v_basic_false1){

    // Testing the flip side
    Card a = Card(FOUR, CLUBS);
    Card b = Card(THREE, DIAMONDS);
    ASSERT_EQUAL(false, Card_less(a, b, SPADES));
}

TEST(test_card_basic_v_basic_false2){

    // Testing that they are equal
    Card a = Card(KING, HEARTS);
    Card b = Card(KING, HEARTS);
    ASSERT_EQUAL(false, Card_less(a, b, DIAMONDS));
}

TEST(test_card_basic_v_basic_true3){

    // Testing that they are equal but also have bower ranks
    Card a = Card(JACK, SPADES);
    Card b = Card(JACK, CLUBS);
    ASSERT_EQUAL(true, Card_less(a, b, HEARTS));
}

// Testing Card_less with led_suit <- same idea as the other Card_less tests
TEST(test_card_left_bower_v_right_bower_led){
    Card a = Card(JACK, DIAMONDS);
    Card b = Card(JACK, HEARTS);
    Card led = Card(TEN, DIAMONDS);
    ASSERT_EQUAL(true, Card_less(a, b, led, HEARTS));
}

TEST(test_card_right_bower_v_left_bower_led){
    Card a = Card(JACK, HEARTS);
    Card b = Card(JACK, DIAMONDS);
    Card led = Card(TEN, DIAMONDS);
    ASSERT_EQUAL(false, Card_less(a, b, led, HEARTS));
}

TEST(test_card_right_bower_v_right_bower_led){
    Card a = Card(JACK, SPADES);
    Card b = Card(JACK, SPADES);
    Card led = Card(JACK, CLUBS);
    ASSERT_EQUAL(false, Card_less(a, b, led, SPADES));
}

TEST(test_card_trump_v_left_bower_led){
    Card a = Card(TEN, CLUBS);
    Card b = Card(JACK, CLUBS);
    Card led = Card(TEN, DIAMONDS);
    ASSERT_EQUAL(true, Card_less(a, b, led, CLUBS));
}

TEST(test_card_left_bower_v_trump_led){
    Card a = Card(JACK, SPADES);
    Card b = Card(QUEEN, SPADES);
    Card led = Card(TEN, DIAMONDS);
    ASSERT_EQUAL(false, Card_less(a, b, led, SPADES));
}

TEST(test_card_trump_v_trump_true_led){
    Card a = Card(NINE, DIAMONDS);
    Card b = Card(ACE, DIAMONDS);
    Card led = Card(TEN, SPADES);
    ASSERT_EQUAL(true, Card_less(a, b, led, DIAMONDS));
}

TEST(test_card_trump_v_trump_false1_led){
    Card a = Card(NINE, DIAMONDS);
    Card b = Card(TWO, DIAMONDS);
    Card led = Card(TEN, SPADES);
    ASSERT_EQUAL(false, Card_less(a, b, led, DIAMONDS));
}

TEST(test_card_trump_v_trump_false2_led){
    Card a = Card(TEN, DIAMONDS);
    Card b = Card(TEN, DIAMONDS);
    Card led = Card(NINE, SPADES);
    ASSERT_EQUAL(false, Card_less(a, b, led, DIAMONDS));
}

TEST(test_card_led_card_v_trump_led){
    Card a = Card(NINE, HEARTS);
    Card b = Card(NINE, DIAMONDS);
    Card led = Card(TEN, HEARTS);
    ASSERT_EQUAL(true, Card_less(a, b, led, DIAMONDS));
}

TEST(test_card_trump_v_led_card_led){
    Card a = Card(ACE, SPADES);
    Card b = Card(ACE, CLUBS);
    Card led = Card(TEN, CLUBS);
    ASSERT_EQUAL(false, Card_less(a, b, led, SPADES));
}

TEST(test_card_led_v_led_card_true_led){
    
    // Testing the led card against a led card true
    Card a = Card(TWO, DIAMONDS);
    Card b = Card(ACE, DIAMONDS);
    Card led = Card(TEN, DIAMONDS);
    ASSERT_EQUAL(true, Card_less(a, b, led, SPADES));
}

TEST(test_card_led_v_led_card_false1_led){

    // Testing a led card against a led card false 
    Card a = Card(ACE, DIAMONDS);
    Card b = Card(FOUR, DIAMONDS);
    Card led = Card(TEN, DIAMONDS);
    ASSERT_EQUAL(false, Card_less(a, b, led, SPADES));
}

TEST(test_card_led_v_led_card_false2_led){

    // Testing a led card against a led card false (equal)
    Card a = Card(TEN, DIAMONDS);
    Card b = Card(TEN, DIAMONDS);
    Card led = Card(JACK, DIAMONDS);
    ASSERT_EQUAL(false, Card_less(a, b, led, SPADES));
}

TEST(test_card_basic_v_led_card_led){
    Card a = Card(ACE, SPADES);
    Card b = Card(ACE, CLUBS);
    Card led = Card(TEN, CLUBS);
    ASSERT_EQUAL(true, Card_less(a, b, led, HEARTS));
}

TEST(test_card_led_card_v_basic_led){
    Card a = Card(ACE, SPADES);
    Card b = Card(ACE, CLUBS);
    Card led = Card(TEN, SPADES);
    ASSERT_EQUAL(false, Card_less(a, b, led, HEARTS));
}

TEST(test_card_basic_v_basic_true_led){
    Card a = Card(TWO, CLUBS);
    Card b = Card(THREE, SPADES);
    Card led = Card(TEN, HEARTS);
    ASSERT_EQUAL(true, Card_less(a, b, led, HEARTS));
}

TEST(test_card_basic_v_basic_false1_led){
    Card a = Card(FOUR, CLUBS);
    Card b = Card(THREE, DIAMONDS);
    Card led = Card(TEN, SPADES);
    ASSERT_EQUAL(false, Card_less(a, b, led, SPADES));
}

TEST(test_card_basic_v_basic_false2_led){
    Card a = Card(KING, HEARTS);
    Card b = Card(KING, HEARTS);
    Card led = Card(TEN, SPADES);
    ASSERT_EQUAL(false, Card_less(a, b, led, DIAMONDS));
}

TEST(test_card_basic_v_basic_true3_led){
    Card a = Card(JACK, SPADES);
    Card b = Card(JACK, CLUBS);
    Card led = Card(TEN, DIAMONDS);
    ASSERT_EQUAL(true, Card_less(a, b, led, HEARTS));
}

// Operator tests
TEST(test_card_operator_less_than_true){
    Card a = Card(EIGHT, SPADES);
    Card b = Card(NINE, HEARTS);
    ASSERT_EQUAL(true, a<b);
}

TEST(test_card_operator_less_than_false1){
    Card a = Card(ACE, SPADES);
    Card b = Card(NINE, HEARTS);
    ASSERT_EQUAL(false, a<b);
}

TEST(test_card_operator_less_than_true2){
    Card a = Card(ACE, SPADES);
    Card b = Card(ACE, HEARTS);
    ASSERT_EQUAL(true, a<b);
}

TEST(test_card_operator_less_than_or_equal_to_true1){
    Card a = Card(SEVEN, SPADES);
    Card b = Card(NINE, HEARTS);
    ASSERT_EQUAL(true, a<=b);
}

TEST(test_card_operator_less_than_or_equal_to_true2){
    Card a = Card(SEVEN, SPADES);
    Card b = Card(SEVEN, HEARTS);
    ASSERT_EQUAL(true, a<=b);
}

TEST(test_card_operator_less_than_or_equal_to_false){
    Card a = Card(KING, SPADES);
    Card b = Card(NINE, HEARTS);
    ASSERT_EQUAL(false, a<=b);
}

TEST(test_card_operator_greater_than_true){
    Card a = Card(QUEEN, SPADES);
    Card b = Card(NINE, HEARTS);
    ASSERT_EQUAL(true, a>b);
}

TEST(test_card_operator_greater_than_false1){
    Card a = Card(QUEEN, SPADES);
    Card b = Card(KING, HEARTS);
    ASSERT_EQUAL(false, a>b);
}

TEST(test_card_operator_greater_than_false2){
    Card a = Card(KING, SPADES);
    Card b = Card(KING, HEARTS);
    ASSERT_EQUAL(false, a>b);
}

TEST(test_card_operator_greater_than_or_equal_to_true1){
    Card a = Card(ACE, SPADES);
    Card b = Card(KING, HEARTS);
    ASSERT_EQUAL(true, a>=b);
}

TEST(test_card_operator_greater_than_or_equal_to_false2){
    Card a = Card(TEN, SPADES);
    Card b = Card(TEN, HEARTS);
    ASSERT_EQUAL(false, a>=b);
}

TEST(test_card_operator_greater_than_or_equal_to_false){
    Card a = Card(NINE, SPADES);
    Card b = Card(TEN, HEARTS);
    ASSERT_EQUAL(false, a>=b);
}

TEST(test_card_operator_equal_to_false){
    Card a = Card(ACE, SPADES);
    Card b = Card(ACE, HEARTS);
    ASSERT_EQUAL(false, a==b);
}

TEST(test_card_operator_equal_to_false2){
    Card a = Card(ACE, SPADES);
    Card b = Card(TWO, HEARTS);
    ASSERT_EQUAL(false, a==b);
}

TEST(test_card_operator_not_equal_to_true){
    Card a = Card(ACE, SPADES);
    Card b = Card(KING, HEARTS);
    ASSERT_EQUAL(true, a!=b);
}

 TEST(test_card_operator_not_equal_to_false){
    Card a = Card(THREE, SPADES);
    Card b = Card(THREE, HEARTS);
    ASSERT_EQUAL(true, a!=b);
}
// Add more test cases here

TEST_MAIN()
