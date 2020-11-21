#define Deck_h

#include "Card.h"
#include <vector>
#include "CardFactory.h"

class Deck : public vector<Card*> {
public:
	Deck() = default;
    //Deck(istream&, const CardFactory*)
	//Card* draw();
	friend ostream& operator<<(ostream&, const Deck&);
};