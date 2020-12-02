#include "deck.h"

// Constructor which accepts an istream and reconstructs the deck from file.
Deck::Deck(istream &in, CardFactory *cf) { *this = (cf->setDeck(in)); }

// Draws top card from deck if not empty, else print error message
Card* Deck::draw()
{
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
ostream & operator<<(ostream & out, Deck *d) {
	for( auto card : *d ) {
        card->print(out); out << " ";
    }
    return out;
}

// Constructor used to return shuffled deck
Deck::Deck(CardFactory* cf) { *this = (*cf).getDeck(); }
