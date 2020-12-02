#include "discardPile.h"
#include <iostream>

//constructor
DiscardPile::DiscardPile(istream &is, CardFactory *cardfactory) { 
    *this = (cardfactory->auxLoadDeck(is)); 
}


//discards the card to the pile
//add the waste card to discard
DiscardPile & DiscardPile::operator+=(Card *card)
{
	(*this).push_back(card);
	return *this;
}

//returns and removes the top card from the discard pile.
Card *DiscardPile::pickUp()
{
    // Draws top card from pile if not empty, else print error message
	if (this->empty()) {
		cout << "Error: Discard pile is empty!" << endl;
		return nullptr;
	}
	else { // Draw top card from pile
		Card* top = this->back();
        this->pop_back();
        return top;
	}
}

//returns but does not remove the top card from the discard pile
Card *DiscardPile::top(){
    return (*this).back();
}
//to insert all the cards in the DiscardPile to an std::ostream
void DiscardPile::print(ostream &output) {
    for (auto i:(*this)) { //loop thru all element in the vector of discardPile
        output<<i;
        std::cout << ", ";
        std::cout << i << ' '; std::cout << '\n';
    }
}

//friend function to insert only the top card of the discard pile to an std::ostream.
//copied from deck
ostream & operator<<(ostream & os, DiscardPile *d) {
	for( auto card : *d ) { card->print(os); os << " "; }
    return os;
}





