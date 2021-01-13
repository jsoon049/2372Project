#include "tradeArea.h"

// Constructor which accepts an istream and reconstruct the TradeArea from file.
TradeArea::TradeArea(istream& is, CardFactory* cardFactory) {
    char c;
    while(is >> c ) { *this += cardFactory->getCardType(c); } // Loop terminates at end of line or invalid input
}

// Adds the card to the trade area but it does not check if it is legal to place the card
TradeArea& TradeArea::operator+=(Card* card) {
    cardList.push_back(card); // Added to back of list
    cardTypes.push_back(card->getName()); // Added to back of list
    return *this;
}

// Returns true if the card can be legally added to the TradeArea, i.e., a card of the same bean is already in trade area
bool TradeArea::legal(Card* lCard) {
    for(Card* cards: cardList) { // Loop through all cards in list
        if(lCard->getName() == cards->getName() ) return true; // Return true if we find card in cardList with same type as parameter card
    }
    return false; // Return false if no card of same bean is in tradeArea already
}

// Removes a card of the corresponding bean name from the trade area.
Card* TradeArea::trade(string bName) { 
    bool flag = false;
    for(auto itr=cardList.begin(); itr != cardList.end(); itr++) { // Use an iterator to iterate through list of cards
        if((flag == false) && ((*itr)->getName() == bName)) { // We found a card with same bean name
            Card* tradedCard = *itr; // Set card to the card found with iterator
            cardList.erase(itr); // Remove the card from iterator
            flag = true; // Makes sure we only delete one card
            return tradedCard;
        }
    }
    return nullptr; // Return null if no card with given type
}

// Returns the number of cards currently in the trade area
int TradeArea::numCards() { return cardList.size(); }

// Insertion operator to insert all the cards of the trade area to an ostream
ostream& operator<<(ostream& os, TradeArea ta) {
    for(Card* cards: ta.cardList) { 
        cards->print(os); 
        os << " ";
    }
    return os;
}
