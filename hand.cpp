
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

//Not sure how to fix the following error under Hand::hand for friend function

//The hand should print all the cards in order.
/*
Hand::Hand(std::ostream &output, CardFactory *cf) {

    for (auto i:(*this)) { //loop thru all element in the vector of hand 
        output<<i;
        std::cout << ", ";
        std::cout << i << ' '; std::cout << '\n';
    }
}
*/