#ifndef discardPile_h
#define discardPile_h

#include <vector>
#include "cardFactory.h"
#include "card.h"

class DiscardPile : public vector<Card*>   {
public:
    DiscardPile(){}; // default constructor
    DiscardPile(istream&,CardFactory*);
    DiscardPile& operator+= (Card*); 
    Card* pickUp(); 
	Card* top();   
    void print(std::ostream&); 
	friend ostream & operator << (ostream &, DiscardPile);
};

#endif