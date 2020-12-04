#include "cardFactory.cpp"
#include "discardPile.h"

// Constructor which accepts an istream and reconstructs the DiscardPile from file.
DiscardPile::DiscardPile(istream &is, CardFactory *cardfactory) { 
    char discard;
	while (is >> discard) { this->push_back(cardfactory->getCardType(discard)); }
}

// Discards the card to the pile 
DiscardPile& DiscardPile::operator+=(Card *card) {
	(*this).push_back(card); // Add card to top of discard pile
	return *this;
}

// Returns and removes the top card from the discard pile.
Card *DiscardPile::pickUp() {
	if (this->empty()) { // Check if deck is empty
		cout << "Error: Discard pile is empty!" << endl;
		return nullptr;
	}
	else { // Draw top card from pile
		Card* top = this->back();
        this->pop_back();
        return top;
	}
}

// Returns but does not remove the top card from the discard pile
Card *DiscardPile::top(){ 
    if(!this->empty()) return (*this).back(); 
    else return nullptr;
}

// Insert all the cards in the DiscardPile to an std::ostream.
void DiscardPile::print(ostream &output) {
     for(Card *card : *this ) { 
        card->print(output); // Print first letter of all cards in discard pile
        output<< " ";
    }
    cout << endl;
}

// Insertion operator (friend) to insert only the top card of the discard pile to an std::ostream.
ostream & operator<<(ostream & os, DiscardPile d) {
    if(!d.empty()) d.top()->print(os); // Print first letter of top card
    return os;
}





