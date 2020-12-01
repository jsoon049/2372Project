#ifndef card_h
#define card_h

#include <iostream>
using namespace std;

class Card {
public:
	virtual int getCardsPerCoin(int) = 0;
	virtual string getName() = 0;
	virtual void print(ostream&) const = 0;

    //friend function that prints any objects
    friend ostream& operator<<(std::ostream& o, const Card& c) {
	    c.print(o);
	    return o;
    }
};
#endif

