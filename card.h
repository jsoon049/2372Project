/*Card.h*/
#include <iostream>
#include <cassert>      //for assert()
using namespace std;
//a card has beans, total in deck value 
//and chain value(chain value has coin value in it)


class Card {
public:
	virtual int getCardsPerCoin(int) = 0;
	virtual string getName() = 0;

//protected:
	virtual void print(ostream&) const = 0;

	/*friend ostream& operator << (ostream& o, const Card& c) {
		c.print(o);
		return o;
	};
	friend ostream& operator << (ostream& o, const Card* c) {
		o << (*c);
		return o;
	};*/
};

