#ifndef deck_h
#define deck_h

#include <vector>
#include "card.h"
#include "cardFactory.h"

class Deck : public vector<Card*> {
public:
	Deck() {}; // default constructor
	Deck(istream&, CardFactory*);
	Card* draw();
	friend ostream & operator << (ostream &, Deck);
	Deck(CardFactory*);
};
#endif