#ifndef tradeArea
#include <vector>
#include <list>
#include <iostream>
#include "card.h"
#include "cardFactory.h"

class TradeArea : public list<Card*> {
public:

    //TradeArea holds cards in a std::list
   // list<Card*>* cards;

    TradeArea(istream&, CardFactory* ); //constructor
    TradeArea& operator += (Card*);//adds the card to the trade area but 
                            //it does not check if it is legal to place the card.
    bool legal(Card*); //returns true if the card can be legally added to the TradeArea, 
                     //i.e., a card of the same bean is already in the TradeArea
    Card* trade(string); //removes a card of the corresponding bean name 
                        //from the trade area.
    int numCards(); //returns the number of cards currently in the trade area.
    friend ostream & operator << (ostream &, TradeArea);//the insertion operator (friend) to insert all the cards of the trade area to an std::ostream.

};
#endif