#include "deck.h"

//** TOP CARD IS BACK OF VECTOR **//

// Constructor which accepts an istream and reconstructs the deck from file.
Deck::Deck(istream &is, CardFactory *cardfactory) { 
	*this = cardfactory->auxLoadDeck(is); 
}

// Draws top card from deck if not empty, else print error message
Card* Deck::draw() {
	if (this->empty()) {
		cout << "Error: Deck is empty!" << endl;
		return nullptr;
	}
	else { // Draw top card from deck
		Card* top = this->back();
        this->pop_back();
        return top;
	}
}

// Insertion operator (friend) to insert all the cards in the deck to an std::ostream.
ostream & operator<<(ostream & os, Deck d) {
	for(Card* card : d) { card->print(os); os << " "; }
    return os;
}

// Constructor used to return shuffled deck
Deck::Deck(CardFactory* cardFactory) { *this = (*cardFactory).getDeck(); }
