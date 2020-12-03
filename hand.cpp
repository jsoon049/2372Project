#include "hand.h"
//** TOP CARD IS FRONT OF QUEUE **//

// Constructor which accepts an istream and reconstruct the Hand from file.
Hand::Hand( istream& is, CardFactory* cardFactory ) {
    char card;
    while(is >> card) hand.push(cardFactory->getCardType(card));  // loop terminates when end of line or invalid input
}

// Adds the card to the rear of the hand.
Hand& Hand::operator+=(Card* c) {
    hand.push(c);
    return *this;
}

// Returns and removes the top card from the player's hand
Card* Hand::play() { 
    if(hand.empty()) { // Check if hand is empty
        cout << "Empty hand!" << endl; 
        return nullptr; // Return null pointer if empty hand
    }
    else { 
        Card* top = hand.front();
        hand.pop();
        return top;
    }
}

// Returns but does not remove the top card from the player's hand
Card* Hand::top() { 
    if(hand.empty()) { // Check if hand is empty
        cout << "Empty hand!" << endl; 
        return nullptr; // Return null pointer if empty hand
    }
    else return hand.front();
}

// Returns and removes the Card at a given index
Card* Hand::operator[](int num) {
    Card* wantedCard = nullptr; 
    if(num < 0 || num >= hand.size()) cout << "Index out of bounds!" << endl;
    else {
        for(int i=0; i<= hand.size(); i++) { 
            if(i == num) wantedCard = hand.front(); // store Card if we found index we are looking for
            else hand.push(hand.front()); // copy front card to back
            hand.pop(); // remove front card
        }
    }
    return wantedCard;
}

// Insertion operator to print Hand on an std::ostream.
ostream& operator<<(ostream& os, Hand copy) { 
    for(int i=0; i < copy.hand.size(); i++) {
        (copy.hand.front())->print(os); 
        os << " ";
        copy.hand.push(copy.hand.front()); // copy front card to back
        copy.hand.pop(); // remove top card
    }
    return os;
}
