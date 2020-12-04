#ifndef card_h
#define card_h

#include <iostream>
#include <exception>
using namespace std;

class Card {
public:
	virtual int getCardsPerCoin(int) = 0;
	virtual string getName() = 0;
	virtual void print(ostream&) const = 0;

    // Friend function that prints any objects
    friend ostream& operator<<(std::ostream& o, const Card& c) {
	    c.print(o);
	    return o;
    }

	// Exception thrown for type errors between cards of different bean types
	struct IllegalType : public exception {
    	const char * err () const throw () { 
        	return "Type Error: Card type does not match chain type!"; 
    	}
	};
};
#endif

