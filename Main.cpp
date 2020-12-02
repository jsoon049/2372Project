#include "card.cpp"
#include "cardFactory.cpp"
#include <string.h>
#include <sstream> 
#include "chain.h"
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
    //TEST CARD TYPES
    // black b;
    // if(b.getName() == "black") cout << "yes" <<endl;
    // cout << b.getCardsPerCoin(3);

    //TEST DECK CONSTRCUTION
    // CardFactory *f = new CardFactory();
    // Deck *d = new Deck(f);
    // cout << d;

    //TEST CHAIN
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

    //TEST RECONSTRCUT CHAIN 
    Chain<black> savedChain;
    black *b = new black();
	auto cardFactory = CardFactory::getFactory();
	for (int i = 0; i < 4; i++) savedChain += (b);
	stringstream save;
    save << savedChain;
	auto loadedChain = Chain<black>(save, cardFactory);
    cout << loadedChain << endl;
    return 0;
}