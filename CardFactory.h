#ifndef cardFactory_h
#define cardFactory_h

#include <random>
#include <chrono>
 
class Deck;

class CardFactory {
private:
	Deck* d;
public:
    CardFactory();
	static CardFactory* getFactory();
	Deck getDeck();
	Card* getCardType(char);
	Deck auxLoadDeck (istream &);
};
#endif