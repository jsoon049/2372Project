#ifndef tradeArea_h
#define tradeArea_h

#include <list>
#include "card.h"
#include "cardFactory.h"

class TradeArea {
public:
    list<Card*> cardList; // List of cards to store cards in TradeArea
    list<string> cardTypes; // List of strings to store types of cards in TradeArea
    TradeArea(){}; // Default constructor
    TradeArea( istream&, CardFactory*);
    TradeArea& operator+=(Card*);
    bool legal(Card*);
    Card* trade(string);
    int numCards();
    friend ostream& operator<<(ostream&, TradeArea);
};
#endif