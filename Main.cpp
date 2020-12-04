#include <string.h>
#include "chain.h"
#include "hand.cpp"
#include "tradeArea.cpp"
#include "player.cpp"
// While there are still cards on the Deck if pause save game to file and exit For each Player
// Display Table
// Player draws top card from Deck If TradeArea is not empty
// Add bean cards from the TradeArea to chains or discard them.
// Play topmost card from Hand.
// If chain is ended, cards for chain are removed and player receives coin(s). If player decides to
// Play the now topmost card from Hand.
// If chain is ended, cards for chain are removed and player receives coin(s). If player decides to
// Show the player's full hand and player selects an arbitrary card
// Discard the arbitrary card from the player's hand and place it on the discard pile. Draw three cards from the deck and place cards in the trade area
// while top card of discard pile matches an existing card in the trade area
// draw the top-most card from the discard pile and place it in the trade area
// end
// for all cards in the trade area
// if player wants to chain the card chain the card.
// else
// card remains in trade area for the next player.
// end
// Draw two cards from Deck and add the cards to the player's hand (at the back).
// end

int main() {
    // //TEST DECK CONSTRCUTION
    // CardFactory *f = CardFactory::getFactory();
    // Deck *d = new Deck(f);
    // cout << d << endl;
    // //TEST IOSTREAM DECK
    // stringstream s;
    // cout << (d->draw())->getName() << endl;
    // cout << (d->draw())->getName() << endl;
    // s << d; 
    // auto *deck2 = new Deck(s, f);
    // cout << deck2 << endl;

    // //TEST CHAIN
    // Chain<Blue> bchain;
    // Blue* bl = new Blue();
    // Green *g;
    // bchain+=(bl);
    // bchain+=(bl);
    // bchain+=(bl);
    // bchain+=(bl);
    // bchain+=(bl);
    // bchain+=(bl);
    // int result = bchain.sell();
    // cout << "res " << result << endl;
    // cout << bchain << endl;
    // //TEST IOSTREAM CHAIN 
    // Chain<black> savedChain;
    // black *b = new black();
	// auto cardFactory = CardFactory::getFactory();
	// for (int i = 0; i < 4; i++) savedChain += (b);
	// stringstream save;
    // save << savedChain;
	// auto loadedChain = Chain<black>(save, cardFactory);
    // cout << loadedChain << endl;

    // //TEST HAND
    // Hand h;
    // Red *r = new Red();
    // soy *s = new soy();
    // garden *gar = new garden();
    // h += r;
    // h += s;
    // h += gar;
    // //cout << h << endl;
    // //TEST HAND IOSTREAM
    // auto cardFactory = CardFactory::getFactory();
	// stringstream save;
    // save << h;
	// auto filehand = Hand(save, cardFactory);
    // cout << filehand << endl;
    // //TEST HAND FUNCTIONS
    // Card *c = h.top();
    // cout << c->getName() << endl;
    // Card *c1 = h.play();
    // cout << c1->getName() << endl;
    // cout << h << endl;
    // Card *c2 = h[1];
    // cout << c2->getName() << endl;
    // cout << h << endl;

    // //TEST DISCARD PILE
    // DiscardPile dpile;
    // Stink *st = new Stink();
    // black *b2 = new black();
    // Green *g2 = new Green();
    // dpile += st;
    // dpile += b2;
    // dpile += g2;
    // //cout << dpile << endl; // Print only last element
    // dpile.print(cout);
    // auto cardFactory = CardFactory::getFactory();
	// stringstream so;
    // so << dpile;
	// auto dpile2 = DiscardPile(so, cardFactory);
    // dpile2.print(cout); // only returns top card b/c of insertion operator
    // //TEST DISCARD FUNCTIONS
    // Card *c5 = dpile.top();
    // c5->print(cout);
    // cout << endl;
    // Card *c6 = dpile.pickUp();
    // c6->print(cout);
    // cout << endl;
    // dpile.print(cout); // Print all elements

    // //TEST TRADE AREA
    // Card *g1 = new Green(), *g2 = new Green(), *r = new Red();
    // Card *g3 = new Green(), *r2 = new Red();
	// auto ta = TradeArea();
	// ta += g1; 
    // cout << ta.legal(g2) << endl;
    // cout << ta.legal(r) << endl;
    // ta += r;
    // ta += g2;
    // stringstream save;
    // save << ta;
    // auto ta2 = TradeArea(save, CardFactory::getFactory());
    // cout << ta << endl;
    // cout << ta2 << endl;
    // cout << ta.numCards() << endl;
    // ta.trade(g3->getName()); //trade from front of list
    // cout << ta << endl;

    //TEST PLAYER   
    Player pl = Player("jeremy");
    pl += 5; //five coins
    pl.buyThirdChain();
    for (int i = 0; i < 4; i++) {
        Green *g1 = new Green();
        (pl.hand)+=g1;
    }
    for (int i = 0; i < 4; i++) {
        Blue *B1 = new Blue();
        (pl.hand)+=B1;
    }
    pl.printHand(cout, true);
    cout << endl;
    Card *r1 = new Red(), *s1 = new soy();
    pl.addChain(0,r1);
    pl.addChain(1,s1);
    cout << pl << endl;
    stringstream save;
    save << pl;
    Player pl2 = Player(save, CardFactory::getFactory());
    cout << pl2 << endl;
    return 0;
}