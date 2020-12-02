#ifndef deck_h
#define deck_h

#include <vector>
#include "card.h"
#include "cardFactory.h"

class cardFactory;

class Deck : public vector<Card*> {
public:
	Deck(istream&, CardFactory*);
	Card* draw();
	friend ostream & operator << (ostream &, Deck d);
	Deck() {}; // default constructor
	Deck(CardFactory*);
};
#endif