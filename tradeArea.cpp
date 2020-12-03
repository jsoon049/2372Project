#include "tradeArea.h"
#include <list>
#include <algorithm>
#include "CardFactory.h"
#include "card.h"
//TradeArea holds cards in a std::list

//constructor
TradeArea::TradeArea(istream &is, CardFactory *cardfactory) {}

//adds the card to the trade area
TradeArea & TradeArea::operator+=(Card *card){
    (*this).push_back(card);
    return *this;
}

//returns true if the card can be legally added to the TradeArea
bool TradeArea::legal(Card *card){
    auto found = std::find(std::begin(*this), std::end(*this), card);
    
    if (found != std::end(*this)) { //does contain that same bean in the area
        return true;
    } else { //does not contain same bean
        return false;
    }
}
//removes a card of the corresponding bean name from the trade area.
//for loop to go thru each card in the trade area(list), 
//if the bean name is the same as the passin string name
//remove that card
/*Card * TradeArea::trade(string name){
    .card.getName()???
}*/


//returns the number of cards currently in the trade area.
int TradeArea::numCards() { 
    return (sizeof(this));
}

//the insertion operator (friend) to insert all the cards of 
    //the trade area to an std::ostream.
//copied from deck
ostream & operator<<(ostream & os, TradeArea *t) {
    for( auto card : *t) { card->print(os); os << " "; }
    return os;
}
