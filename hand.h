#include <vector>
#include "cardFactory.h"
#include "card.h"

class Hand : public vector<Card*> {
private:


public:
    //constructor
    Hand(istream&, CardFactory*); 
    //Hand() = default;     
    Hand& operator+=(Card*); //adds the card to the rear of the hand.       
    Card* play(); //returns and removes the top card from the player's hand.    
    Card* top();  //returns but does not remove the top card from the player's hand.                    
    Card* operator[](int);      //returns and removes the Card at a given index.
    friend ostream & operator << (ostream &, Hand);
    void print(std::ostream &out);
};