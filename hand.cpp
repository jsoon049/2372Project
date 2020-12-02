
#include "hand.h"
#include <string>
#include <iostream>

//Question: do i need "*this"??? or is using "this" is enough
//assume back of the vector is the top card on hand

//constructor
Hand::Hand(istream &is, CardFactory *cardfactory) {}

//adds the card to the rear of the hand.
Hand &Hand::operator+=(Card *card) {
    (*this).push_back(card);  //push the elements into a vector from the back
    return *this;
}
//returns and removes the top card from the player's hand.
Card *Hand :: play() {

    Card *topCard = (*this).back(); //saves the top card 
    (*this).pop_back();  //pop or remove elements from a vector from the back.
                        //aka remove the top card from hand
    return topCard;

}

//returns but does not remove the top card from the player's hand.
Card* Hand ::top() {
    return (*this).back();
}

//returns and removes the Card at a given index.
Card* Hand ::operator[](int index) {
    Card *toBeRemoved = (*this).at(index); //saves the card value that is tobe removed
    (*this).erase((*this).begin() + index);//remove that card
    return toBeRemoved;
}


//The hand should print all the cards in order.
//copied from deck
ostream & operator<<(ostream & os, Hand *h) {
	for( auto card : *h) { card->print(os); os << " "; }
    return os;
}
