#include "deck.h"

// Constructor which accepts an istream and reconstructs the deck from file.
Deck::Deck(istream &in, CardFactory *cf)
{
	*this = (cf->setDeck(in));
	// deck = new Deck();
	// char cardType[256];
	// in.getline(cardType, 256);
	// int i = 0;
	// while (cardType[i] != NULL) {
	// 	Card* cardToAdd = cf->getCardType(cardType[i]);
	// 	deck->push_back(cardToAdd);									
	// 	i++;
	// }
	// return *deck;
}

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
ostream & operator<<(ostream & out, Deck d) {
	// for (vector<Card*>::iterator it = d.begin(); it != d.end(); it++) {
	// 	out << (*it);
	// }
	// return out;
	for( auto card : d ) {
        card->print(out); out << " ";
    }
    return out;
}

Deck::Deck(CardFactory* cf) { *this = (*cf).getDeck(); }
