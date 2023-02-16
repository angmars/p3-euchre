// Project UID 1d9f47bfc76643019cfbf037641defe1

// #include "Player.h"
// #include "unit_test_framework.h"

// #include <iostream>

// using namespace std;

// TEST(test_player_get_name) {
//     Player * alice = Player_factory("Alice", "Simple");
//     ASSERT_EQUAL("Alice", alice->get_name());

//     delete alice;
// }

// TEST(test_player_add_card){

// }



// // Add more tests here

// TEST_MAIN()


#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

TEST(test_simple_player_ctor) {
    Player* vishnu = Player_factory("Vishnu", "Simple");
    ASSERT_EQUAL("Vishnu", vishnu -> get_name());
    delete vishnu;
}

// idk how to test this one cuz there's nothing returned 
// and we can't access any of the member variables
TEST(test_add_card_basic) {
    Player* eric = Player_factory("Eric", "Simple");
    Card c1 = Card(QUEEN, HEARTS);
    eric -> add_card(c1);
    ASSERT_EQUAL(true, true);
    delete eric;
}

// idk how to test this one cuz there's nothing returned 
// and we can't access any of the member variables
TEST(test_add_card) {
    Player* eric = Player_factory("Eric", "Simple");
    Card c1 = Card(QUEEN, HEARTS);
    eric -> add_card(c1); // (*eric).add_card(c1);
    Card c2 = Card(NINE, CLUBS);
    eric -> add_card(c2); // (*eric).add_card(c1);
    delete eric;
}

TEST(test_make_trump_round_one) {
    Player* eric = Player_factory("Eric", "Simple");
    Card upcard(NINE, SPADES);

    Card ec1 = Card(JACK, SPADES);
    Card ec2 = Card(TEN, CLUBS);
    Card ec3 = Card(KING, SPADES);
    Card ec4 = Card(NINE, HEARTS);
    Card ec5 = Card(JACK, HEARTS);
    eric -> add_card(ec1);
    eric -> add_card(ec2);
    eric -> add_card(ec3);
    eric -> add_card(ec4);
    eric -> add_card(ec5);

    Suit order_up_suit = CLUBS;
    ASSERT_TRUE(eric -> make_trump(upcard, false, 1, order_up_suit));
    ASSERT_EQUAL(order_up_suit, SPADES);
    delete eric;

    Player* vishnu = Player_factory("Vishnu", "Simple");
    Card upcard2(NINE, HEARTS);

    const Card vc1(JACK, SPADES);
    const Card vc2(TEN, CLUBS);
    const Card vc3(QUEEN, DIAMONDS);
    const Card vc4(NINE, HEARTS);
    const Card vc5(JACK, DIAMONDS);
    vishnu -> add_card(vc1);
    vishnu -> add_card(vc2);
    vishnu -> add_card(vc3);
    vishnu -> add_card(vc4);
    vishnu -> add_card(vc5);

    Suit order_up_suit2 = CLUBS;
    ASSERT_FALSE(vishnu -> make_trump(upcard2, false, 1, order_up_suit2));
    ASSERT_NOT_EQUAL(order_up_suit, HEARTS);
    delete vishnu;
}

TEST(test_make_trump_round_two) {
    Player* eric = Player_factory("Eric", "Simple");
    Card upcard(NINE, SPADES);
    Card ec1 = Card(ACE, CLUBS);
    Card ec2 = Card(TEN, CLUBS);
    Card ec3 = Card(NINE, SPADES);
    Card ec4 = Card(NINE, HEARTS);
    Card ec5 = Card(JACK, HEARTS);
    eric -> add_card(ec1);
    eric -> add_card(ec2);
    eric -> add_card(ec3);
    eric -> add_card(ec4);
    eric -> add_card(ec5);
    // case in which player should order up
    // upcard is spades, order up should be clubs (r2) 
    Suit order_up_suit = HEARTS;
    ASSERT_TRUE(eric -> make_trump(upcard, false, 2, order_up_suit));
    ASSERT_EQUAL(order_up_suit, CLUBS);
    delete eric;

    Player* vishnu = Player_factory("Vishnu", "Simple");
    Card upcard2(NINE, HEARTS);
    const Card vc1(ACE, HEARTS);
    const Card vc2(KING, HEARTS);
    const Card vc3(TEN, DIAMONDS);
    const Card vc4(NINE, CLUBS);
    const Card vc5(JACK, CLUBS);
    vishnu -> add_card(vc1);
    vishnu -> add_card(vc2);
    vishnu -> add_card(vc3);
    vishnu -> add_card(vc4);
    vishnu -> add_card(vc5);
    // case in which player should not order up
    Suit order_up_suit2 = CLUBS;
    ASSERT_FALSE(vishnu -> make_trump(upcard2, false, 2, order_up_suit2));
    ASSERT_EQUAL(order_up_suit2, CLUBS);
    // screw the dealer case
    ASSERT_TRUE(vishnu -> make_trump(upcard2, true, 2, order_up_suit2));
    ASSERT_EQUAL(order_up_suit2, DIAMONDS);
    delete vishnu;

    Player* tom = Player_factory("Tom", "Simple");
    Card upcard3(NINE, HEARTS);
    const Card tc1(ACE, HEARTS);
    const Card tc2(KING, HEARTS);
    const Card tc3(TEN, DIAMONDS);
    const Card tc4(NINE, CLUBS);
    const Card tc5(JACK, HEARTS);
    tom -> add_card(tc1);
    tom -> add_card(tc2);
    tom -> add_card(tc3);
    tom -> add_card(tc4);
    tom -> add_card(tc5);
    Suit order_up_suit3 = CLUBS;
    ASSERT_TRUE(tom -> make_trump(upcard3, false, 2, order_up_suit3));
    ASSERT_EQUAL(order_up_suit3, DIAMONDS);
    delete tom;
}

TEST(test_add_or_discard) {
    Player* dennis1 = Player_factory("Dennis", "Simple");
    const Card dc1(ACE, CLUBS);
    const Card dc2(TEN, CLUBS);
    const Card dc3(NINE, SPADES);
    const Card dc4(NINE, HEARTS);
    const Card dc5(ACE, HEARTS);
    const Card orderUp1(QUEEN, DIAMONDS);
    dennis1 -> add_card(dc1);
    dennis1 -> add_card(dc2);
    dennis1 -> add_card(dc3);
    dennis1 -> add_card(dc4);
    dennis1 -> add_card(dc5);
    dennis1 -> add_and_discard(orderUp1);
    const Card dl1(KING, DIAMONDS);
    Card d1 = dennis1 -> play_card(dl1, SPADES);
    ASSERT_EQUAL(d1, orderUp1);
    
    delete dennis1;

    Player* dennis2 = Player_factory("Dennis", "Simple");
    const Card dc6(ACE, CLUBS);
    const Card dc7(TEN, CLUBS);
    const Card dc8(NINE, SPADES);
    const Card dc9(NINE, HEARTS);
    const Card dc10(ACE, HEARTS);
    const Card orderUp2(QUEEN, DIAMONDS);
    dennis2 -> add_card(dc6);
    dennis2 -> add_card(dc7);
    dennis2 -> add_card(dc8);
    dennis2 -> add_card(dc9);
    dennis2 -> add_card(dc10);
    dennis2 -> add_and_discard(orderUp2);
    const Card dl2(TEN, SPADES);
    Card d2 = dennis2 -> play_card(dl2, CLUBS);
    ASSERT_FALSE(d2 == dc8);

    delete dennis2;


    Player* dennis3 = Player_factory("Dennis", "Simple");
    const Card dc11(ACE, CLUBS);
    const Card dc12(TEN, CLUBS);
    const Card dc13(NINE, SPADES);
    const Card dc14(NINE, HEARTS);
    const Card dc15(ACE, HEARTS);
    const Card orderUp3(QUEEN, DIAMONDS);
    dennis3 -> add_card(dc11);
    dennis3 -> add_card(dc12);
    dennis3 -> add_card(dc13);
    dennis3 -> add_card(dc14);
    dennis3 -> add_card(dc15);
    dennis3 -> add_and_discard(orderUp3);
    const Card dl3(NINE, DIAMONDS);
    Card d3 = dennis3 -> play_card(dl3, SPADES);
    ASSERT_EQUAL(orderUp3, d3);
    ASSERT_FALSE(d3 == dc13);
    
    delete dennis3;

    // tests if add and discard both upcards
    Player* dennis4 = Player_factory("Dennis", "Simple");
    const Card dc16(ACE, CLUBS);
    const Card dc17(KING, CLUBS);
    const Card dc18(QUEEN, CLUBS);
    const Card dc19(JACK, CLUBS);
    const Card dc20(TEN, CLUBS);

    const Card orderUp4(NINE, CLUBS);
    dennis4 -> add_card(dc16);
    dennis4 -> add_card(dc17);
    dennis4 -> add_card(dc18);
    dennis4 -> add_card(dc19);
    dennis4 -> add_card(dc20);
    dennis4 -> add_and_discard(orderUp4);
    const Card dl4(NINE, DIAMONDS);
    Card d4 = dennis4 -> play_card(dl4, HEARTS);
    ASSERT_EQUAL(d4, dc20);
    delete dennis4;
}

TEST(test_lead_card) {
    // When a Simple Player leads a trick, they play the highest non-trump card in their hand. 
    // If they have only trump cards, they play the highest trump card in their hand.
    Player* eric = Player_factory("Eric", "Simple");
    Card ec1 = Card(ACE, CLUBS);
    Card ec2 = Card(TEN, CLUBS);
    Card ec3 = Card(NINE, SPADES);
    Card ec4 = Card(NINE, HEARTS);
    Card ec5 = Card(ACE, HEARTS);
    eric -> add_card(ec1);
    eric -> add_card(ec2);
    eric -> add_card(ec3);
    eric -> add_card(ec4);
    eric -> add_card(ec5);
    Card c1 = eric -> lead_card(CLUBS);
    ASSERT_EQUAL(c1, ec5);
    Card c2 = eric -> lead_card(HEARTS);
    ASSERT_EQUAL(c2, ec1);
    Card c30 = eric -> lead_card(DIAMONDS);
    ASSERT_EQUAL(c30, ec2);
    delete eric;

    Player* chris = Player_factory("Chris", "Simple");
    const Card cc1(ACE, CLUBS);
    const Card cc2(TEN, CLUBS);
    const Card cc3(NINE, SPADES);
    const Card cc4(NINE, HEARTS);
    const Card cc5(ACE, HEARTS);
    chris -> add_card(cc1);
    chris -> add_card(cc2);
    chris -> add_card(cc3);
    chris -> add_card(cc4);
    chris -> add_card(cc5);
    Card c3 = chris -> lead_card(DIAMONDS);
    ASSERT_EQUAL(c3, cc1);
    delete chris;

    Player* vishnu = Player_factory("Vishnu", "Simple");
    const Card vc1(ACE, CLUBS);
    const Card vc2(JACK, SPADES);
    const Card vc3(QUEEN, CLUBS);
    const Card vc4(NINE, CLUBS);
    const Card vc5(KING, CLUBS);
    vishnu -> add_card(vc1);
    vishnu -> add_card(vc2);
    vishnu -> add_card(vc3);
    vishnu -> add_card(vc4);
    vishnu -> add_card(vc5);
    Card c4 = vishnu -> lead_card(CLUBS);
    Card c5 = vishnu -> lead_card(HEARTS);
    ASSERT_EQUAL(c4, vc2);
    ASSERT_EQUAL(c5, vc1);
    delete vishnu;

    Player* tom = Player_factory("Tom", "Simple");
    const Card tc1(ACE, HEARTS);
    const Card tc2(QUEEN, HEARTS);
    const Card tc3(JACK, HEARTS);
    const Card tc4(NINE, HEARTS);
    const Card tc5(KING, HEARTS);
    tom -> add_card(tc1);
    tom -> add_card(tc2);
    tom -> add_card(tc3);
    tom -> add_card(tc4);
    tom -> add_card(tc5);
    Card c6 = tom -> lead_card(HEARTS);
    ASSERT_EQUAL(c6, tc3);
    delete tom;

    Player* albert = Player_factory("Albert", "Simple");
    const Card ac1(KING, HEARTS);
    const Card ac2(JACK, DIAMONDS);
    const Card ac3(TEN, HEARTS);
    const Card ac4(ACE, HEARTS);
    const Card ac5(QUEEN, HEARTS);
    albert -> add_card(ac1);
    albert -> add_card(ac2);
    albert -> add_card(ac3);
    albert -> add_card(ac4);
    albert -> add_card(ac5);
    Card c7 = albert -> lead_card(HEARTS);
    Card c8 = albert -> lead_card(DIAMONDS);
    ASSERT_EQUAL(c7, ac2);
    ASSERT_EQUAL(c8, ac4);
    delete albert;

    Player* jack = Player_factory("Jack", "Simple");
    const Card jc1(NINE, SPADES);
    const Card jc2(QUEEN, SPADES);
    const Card jc3(QUEEN, CLUBS);
    const Card jc4(TEN, CLUBS);
    const Card jc5(NINE, HEARTS);
    jack -> add_card(jc1);
    jack -> add_card(jc2);
    jack -> add_card(jc3);
    jack -> add_card(jc4);
    jack -> add_card(jc5);
    Card c9 = jack -> lead_card(HEARTS);
    ASSERT_EQUAL(c9, jc3);
    delete jack;

    Player* kaden = Player_factory("Kaden", "Simple");
    const Card kc1(ACE, HEARTS);
    const Card kc2(JACK, DIAMONDS);
    const Card kc3(JACK, HEARTS);
    const Card kc4(NINE, HEARTS);
    const Card kc5(KING, HEARTS);
    kaden -> add_card(kc1);
    kaden -> add_card(kc2);
    kaden -> add_card(kc3);
    kaden -> add_card(kc4);
    kaden -> add_card(kc5);
    Card c10 = kaden -> lead_card(HEARTS);
    ASSERT_EQUAL(c10, kc3);
    delete kaden;
}

TEST(test_play_card) {
   // If a Simple Player can follow suit, they play the highest card that follows suit. 
   // Otherwise, they play the lowest card in their hand.
    Player* eric = Player_factory("Eric", "Simple");
    Card ec1 = Card(ACE, CLUBS);
    Card ec2 = Card(TEN, DIAMONDS);
    Card ec3 = Card(JACK, DIAMONDS);
    Card ec4 = Card(KING, DIAMONDS);
    Card ec5 = Card(ACE, HEARTS);

    const Card lC1(QUEEN, CLUBS);
    const Card lC2(QUEEN, DIAMONDS);
    const Card lC3(QUEEN, SPADES);
    eric -> add_card(ec1);
    eric -> add_card(ec2);
    eric -> add_card(ec3);
    eric -> add_card(ec4);
    eric -> add_card(ec5);
    Card c1 = eric -> play_card(lC1, CLUBS);
    ASSERT_EQUAL(c1, ec1);
    Card c2 = eric -> play_card(lC2, CLUBS);
    Card c3 = eric -> play_card(lC2, HEARTS);
    Card c4 = eric -> play_card(lC3, HEARTS);
    ASSERT_EQUAL(c2, ec4);
    ASSERT_EQUAL(c3, ec2);
    ASSERT_EQUAL(c4, ec5);
    delete eric;

    Player* vishnu = Player_factory("Vishnu", "Simple");
    const Card vc1(TEN, DIAMONDS);
    const Card vc2(JACK, DIAMONDS);
    const Card vc3(QUEEN, CLUBS);
    const Card vc4(TEN, HEARTS);
    const Card vc5(KING, CLUBS);

    const Card lC4(QUEEN, DIAMONDS);
    const Card lC5(QUEEN, SPADES);
    vishnu -> add_card(vc1);
    vishnu -> add_card(vc2);
    vishnu -> add_card(vc3);
    vishnu -> add_card(vc4);
    vishnu -> add_card(vc5);
    Card c5 = vishnu -> play_card(lC4, HEARTS);
    ASSERT_EQUAL(c5, vc1);
    delete vishnu;

    Player* tom = Player_factory("Vishnu", "Simple");
    const Card tc1(ACE, CLUBS);
    const Card tc2(ACE, HEARTS);
    const Card tc3(QUEEN, CLUBS);
    const Card tc4(TEN, HEARTS);
    const Card tc5(KING, CLUBS);

    const Card lC6(QUEEN, SPADES);
    tom -> add_card(tc1);
    tom -> add_card(tc2);
    tom -> add_card(tc3);
    tom -> add_card(tc4);
    tom -> add_card(tc5);
    Card c6 = tom -> play_card(lC6, HEARTS);
    ASSERT_EQUAL(c6, tc3);
    delete tom;
}

TEST_MAIN()