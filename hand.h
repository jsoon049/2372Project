#ifndef hand_h
#define hand_h

#include <queue>
#include "cardFactory.h"
#include "card.h"

class Hand : public vector<Card*> {
public:
    queue<Card*> hand;
    Hand() = default;   
    Hand(istream&, CardFactory*);   
    Hand& operator+=(Card*);       
    Card* play();    
    Card* top();                
    Card* operator[](int);      
    friend ostream & operator << (ostream &, Hand);
};
#endif