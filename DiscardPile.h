/*discardPile.h*/
#ifndef discardPile.h
#define discardPile.h

#include <vector>
#include "CardFactory.h"
#include "card.h"

class DiscardPile : public vector<Card*>   {
public:

    //DiscardPile(istream&, const CardFactory*);constructor
    DiscardPile(istream&,CardFactory*);//constructor
    DiscardPile& operator+= (Card*); //discards the card to the pile.
    Card* pickUp(); //returns and removes the top card from the discard pile.
	Card* top();   //returns but does not remove the top card from the discard pile.
    void print(std::ostream&); //to insert all the cards in the DiscardPile to an std::ostream
	friend ostream & operator << (ostream &, DiscardPile);
};

#endif