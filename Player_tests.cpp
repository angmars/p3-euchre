//Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * hudson = Player_factory("Hudson", "Simple");
    ASSERT_EQUAL("Hudson", hudson->get_name());

    delete hudson;
}

TEST(test_player_add_card){
    Player * albert = Player_factory("Albert", "Simple");
    const Card card1 = Card(QUEEN, SPADES);
    const Card card2 = Card(KING, HEARTS);
    albert->add_card(card1);
    albert->add_card(card2);

    // I can't assert anything so ig it works LMFAO

    delete albert;
}

TEST(test_player_make_trump_1){

    Player * vishnu = Player_factory("Vishnu", "Simple");
    const Card card1 = Card(JACK, SPADES);
    const Card card2 = Card(KING, CLUBS);
    const Card card3 = Card(JACK, HEARTS);
    const Card card4 = Card(NINE, SPADES);
    const Card card5 = Card(JACK, DIAMONDS);

    vishnu->add_card(card1);
    vishnu->add_card(card2);
    vishnu->add_card(card3);
    vishnu->add_card(card4);
    vishnu->add_card(card5);

    Suit order_up_suit;

    //Makes trump because has both left and right bowers
    const Card upcard1 = Card(ACE, DIAMONDS);
    
    ASSERT_TRUE(vishnu->make_trump(upcard1, true, 1, order_up_suit));
    ASSERT_EQUAL(order_up_suit, DIAMONDS);

    //Doesn't make trump because only one right bower even though another trump
    const Card upcard2 = Card(TEN, SPADES);

    ASSERT_FALSE(vishnu->make_trump(upcard2, false, 1, order_up_suit));

    //Makes the trump because there's one face card with a club
    ASSERT_TRUE(vishnu->make_trump(upcard2, false, 2, order_up_suit));
    ASSERT_EQUAL(order_up_suit, CLUBS);

    // Makes trump because has left bower and one face trump
    const Card upcard3 = Card(NINE, CLUBS);

    ASSERT_TRUE(vishnu->make_trump(upcard3, false, 1, order_up_suit));
    ASSERT_EQUAL(order_up_suit, CLUBS);

    delete vishnu;
}

TEST(test_player_make_trump_2){

    Player * jack = Player_factory("Jack", "Simple");
    const Card card1 = Card(JACK, DIAMONDS);
    const Card card2 = Card(TEN, SPADES);
    const Card card3 = Card(NINE, DIAMONDS);
    const Card card4 = Card(TEN, HEARTS);
    const Card card5 = Card(NINE, HEARTS);

    jack->add_card(card1);
    jack->add_card(card2);
    jack->add_card(card3);
    jack->add_card(card4);
    jack->add_card(card5);

    Suit order_up_suit;

    //Doesn't make trump because no clubs
    const Card upcard1 = Card(ACE, SPADES);
    
    ASSERT_FALSE(jack->make_trump(upcard1, false, 2, order_up_suit));

   //Makes suit because left bower
    const Card upcard2 = Card(KING, DIAMONDS);

    ASSERT_TRUE(jack->make_trump(upcard2, false, 2, order_up_suit));
    ASSERT_EQUAL(order_up_suit, HEARTS);

    //Doesn't make suit because both bad cards
    const Card upcard3 = Card(KING, HEARTS);

    ASSERT_TRUE(jack->make_trump(upcard3, false, 2, order_up_suit));
    ASSERT_EQUAL(order_up_suit, DIAMONDS);

    //Doesn't make suit because doesn't have a face spade
    const Card upcard4 = Card(JACK, CLUBS);

    ASSERT_FALSE(jack->make_trump(upcard4, false, 2, order_up_suit));

    //Chooses Clubs anyways because the dealer has to choose so it chooses the opposite
    ASSERT_TRUE(jack->make_trump(upcard1, true, 2, order_up_suit));
    ASSERT_EQUAL(order_up_suit, CLUBS);

    ASSERT_TRUE(jack->make_trump(upcard4, true, 2, order_up_suit));
    ASSERT_EQUAL(order_up_suit, SPADES);


    delete jack;
}

TEST(test_player_add_and_discard1){
    Player *eric = Player_factory("Eric", "Simple");
    const Card card1 = Card(QUEEN, SPADES);
    const Card card2 = Card(NINE, HEARTS);
    const Card card3 = Card(JACK, DIAMONDS);
    const Card card4 = Card(KING, SPADES);
    const Card card5 = Card(NINE, CLUBS);

    eric -> add_card(card1);
    eric -> add_card(card2);
    eric -> add_card(card3);
    eric -> add_card(card4);
    eric -> add_card(card5);

    //Adds the card and takes out the nine hearts
    const Card upcard1 = Card(ACE, CLUBS);
    const Card led1 = Card(QUEEN, CLUBS);

    eric->add_and_discard(upcard1);

    //Plays the new card
    ASSERT_EQUAL(upcard1, eric->play_card(led1, CLUBS));

    //Adds the card and gets rid of the nine of clubs
    const Card upcard2 = Card(QUEEN, HEARTS);
    const Card led2 = Card(JACK, HEARTS);

    eric->add_and_discard(upcard2);

    //Plays the Jack of Diamonds (left bower)
    ASSERT_EQUAL(card3, eric->play_card(led2, HEARTS));

    delete eric;
}

TEST(test_player_add_and_discard2){
    Player *kaden = Player_factory("Kaden", "Simple");
    
    const Card card1 = Card(ACE, SPADES);
    const Card card2 = Card(TEN, HEARTS);
    const Card card3 = Card(NINE, CLUBS);
    const Card card4 = Card(QUEEN, SPADES);
    const Card card5 = Card (KING, CLUBS);

    kaden -> add_card(card1);
    kaden -> add_card(card2);
    kaden -> add_card(card3);
    kaden -> add_card(card4);
    kaden -> add_card(card5);

    //Adds Jack of spades in place of Nine of clubs
    const Card upcard1 = Card(JACK, SPADES);
    const Card led1 = Card(TEN, DIAMONDS);

    kaden -> add_and_discard(upcard1);

    //Plays nine of spades
    ASSERT_EQUAL(card2, kaden->play_card(led1, DIAMONDS))

    //Adds ace of clubs and gets rid of ten of hearts
    const Card upcard2 = Card(ACE, CLUBS);
    const Card led2 = Card(TEN, CLUBS);

    kaden -> add_and_discard(upcard2);

    //Plays Nine of hearts
    ASSERT_EQUAL(upcard1, kaden->play_card(led2, CLUBS));

    delete kaden;
}

TEST(test_player_lead_card1){
    Player *kaitlyn = Player_factory("Kaitlyn", "Simple");

    const Card card1 = Card(NINE, HEARTS);
    const Card card2 = Card(TEN, HEARTS);
    const Card card3 = Card(JACK, HEARTS);
    const Card card4 = Card(QUEEN, HEARTS);
    const Card card5 = Card(KING, HEARTS);

    kaitlyn->add_card(card1);
    kaitlyn->add_card(card2);
    kaitlyn->add_card(card3);
    kaitlyn->add_card(card4);
    kaitlyn->add_card(card5);

    ASSERT_EQUAL(card5, kaitlyn->lead_card(HEARTS));

    const Card upcard1 = Card(ACE, HEARTS);

    // Gets rid of Queen of Hearts
    kaitlyn->play_card(upcard1, SPADES);

    ASSERT_EQUAL(card3, kaitlyn->lead_card(HEARTS));

    delete kaitlyn;
}

TEST(test_player_lead_card2){
    Player *sam = Player_factory("Sam", "Simple");

    const Card card1 = Card(NINE, SPADES);
    const Card card2 = Card(NINE, CLUBS);
    const Card card3 = Card(TEN, HEARTS);
    const Card card4 = Card(TEN, DIAMONDS);
    const Card card5 = Card(JACK, CLUBS);

    sam->add_card(card1);
    sam->add_card(card2);
    sam->add_card(card3);
    sam->add_card(card4);
    sam->add_card(card5);

    ASSERT_EQUAL(card4, sam->lead_card(CLUBS));

    const Card upcard1 = Card(JACK, HEARTS);

    sam->play_card(upcard1, CLUBS);

    ASSERT_EQUAL(card1, sam->lead_card(CLUBS));

    delete sam;
}

TEST(test_player_play_card1){
    Player *dajias1 = Player_factory("Matthew", "Simple");

    const Card card1 = Card(ACE, HEARTS);
    const Card card2 = Card(JACK, DIAMONDS);
    const Card card3 = Card(NINE, DIAMONDS);
    const Card card4 = Card(JACK, CLUBS);
    const Card card5 = Card(JACK, SPADES);

    dajias1->add_card(card1);
    dajias1->add_card(card2);
    dajias1->add_card(card3);
    dajias1->add_card(card4);
    dajias1->add_card(card5);

    const Card upcard1 = Card(TEN, DIAMONDS);
    ASSERT_EQUAL(card3, dajias1->play_card(upcard1, SPADES));

    const Card upcard2 = Card(NINE, SPADES);
    ASSERT_EQUAL(card5, dajias1->play_card(upcard2, SPADES));

    const Card upcard3 = Card(QUEEN, SPADES);
    ASSERT_EQUAL(card4, dajias1-> play_card(upcard3, SPADES));

    const Card upcard4 = Card(QUEEN, HEARTS);
    ASSERT_EQUAL(card1, dajias1->play_card(upcard4, DIAMONDS));

    delete dajias1;
}

TEST(test_player_play_card2){
    Player *dajias2 = Player_factory("Kevin", "Simple");

    const Card card1 = Card(JACK, HEARTS);
    const Card card2 = Card(ACE, DIAMONDS);
    const Card card3 = Card(TEN, SPADES);
    const Card card4 = Card(JACK, SPADES);
    const Card card5 = Card(ACE, CLUBS);

    dajias2->add_card(card1);
    dajias2->add_card(card2);
    dajias2->add_card(card3);
    dajias2->add_card(card4);
    dajias2->add_card(card5);

    const Card upcard1 = Card(NINE, HEARTS);
    ASSERT_EQUAL(card3, dajias2->play_card(upcard1, DIAMONDS));

    const Card upcard2 = Card(NINE, DIAMONDS);
    ASSERT_EQUAL(card1, dajias2->play_card(upcard2, DIAMONDS));

    const Card upcard3 = Card(NINE, CLUBS);
    ASSERT_EQUAL(card4, dajias2->play_card(upcard3, CLUBS));

    const Card upcard4 = Card(NINE, SPADES);
    ASSERT_EQUAL(card5, dajias2->play_card(upcard4, HEARTS));

    delete dajias2;
}


// Add more tests here

TEST_MAIN()