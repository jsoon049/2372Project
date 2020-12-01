#ifndef cardFactory_h
#define cardFactory_h

#include <random>
#include <iterator>
#include <chrono>
 
class Deck;

class CardFactory {
private:
	Deck* deck;
public:
    CardFactory();
	static CardFactory* getFactory();
	Deck getDeck();
	Card* getCardType(char);
	Deck setDeck (istream &);
};
#endif