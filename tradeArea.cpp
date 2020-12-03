#include "tradeArea.h"

// Constructor which accepts an istream and reconstruct the TradeArea from file.
TradeArea::TradeArea( istream& is, CardFactory* cardFactory) {
    char c;
    while(is >> c ) { *this += cardFactory->getCardType(c); } // loop terminates at end of line or invalid input
}

// Adds the card to the trade area but it does not check if it is legal to place the card
TradeArea& TradeArea::operator+=( Card* card) {
    cardList.push_back(card); // added to back of list
    cardTypes.push_back(card->getName()); // added to back of list
    return *this;
}

// Returns true if the card can be legally added to the TradeArea, i.e., a card of the same bean is already in trade area
bool TradeArea::legal( Card* lCard ) {
    for(Card* cards: cardList) { // loop through all cards in list
        if(lCard->getName() == cards->getName() ) return true; // return true if we find card in cardList with same type as parameter card
    }
    return false; // return false if no card of same bean is in tradeArea already
}

// Removes a card of the corresponding bean name from the trade area.
Card* TradeArea::trade(string bName) { 
    for(auto itr=cardList.begin(); itr != cardList.end(); itr++) { // use iterator to go through list of cards
        if((*itr)->getName() == bName) { // we found a card with same bean name
            Card* tradedCard = *itr; // set card to the card found with iterator
            cardList.erase(itr); // remove the card from iterator
            return tradedCard;
        }
    }
    return nullptr; // return null if no card with given type
}

// Returns the number of cards currently in the trade area
int TradeArea::numCards() { return cardList.size(); }

// Insertion operator to insert all the cards of the trade area to an ostream
ostream& operator<<( ostream& os, TradeArea ta ) {
    for(Card* cards: ta.cardList) { 
        cards->print(os); 
        os << " ";
    }
    return os;
}
