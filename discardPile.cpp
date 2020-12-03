#include "cardFactory.cpp"
#include "discardPile.h"

// Constructor which accepts an istream and reconstructs the DiscardPile from file.
DiscardPile::DiscardPile(istream &is, CardFactory *cardfactory) { 
    // char discard[300];
	// is.getline(discard, 300);
    // int i = 0;
	// while (discard[i] != '\0') {
    //     Card *addDiscard = cardfactory->getCardType(discard[i]);
	// 	if(addDiscard != NULL) { // if card exists
    //         addDiscard->print(cout);
    //         (*this).push_back(addDiscard); // add card to deck						
	// 	}			
	// 	i++;								
	// }
    char discard;
	while (is >> discard) {
		this->push_back(cardfactory->getCardType(discard));
	}
}

// Discards the card to the pile 
DiscardPile & DiscardPile::operator+=(Card *card) {
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
Card *DiscardPile::top(){ return (*this).back(); }

// Insert all the cards in the DiscardPile to an std::ostream.
void DiscardPile::print(ostream &output) {
     for( auto card : *this ) { 
        card->print(output); // Print first letter of all cards
        output<< " ";
    }
    cout << endl;
}

// Insertion operator (friend) to insert only the top card of the discard pile to an std::ostream.
ostream & operator<<(ostream & os, DiscardPile d) {
    if(!d.empty()) d.top()->print(os); // Print first letter of top card
    return os;
}





