
#include "hand.h"
#include <string>
#include <iostream>

//assume back of the vector is the top card on hand

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
Card* Hand ::top() {
    return (*this).back();
}

