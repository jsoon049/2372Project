#ifndef chain_h
#define chain_h
#include <vector>
#include "chainBase.h"
#include <exception>

// class IllegalType : public exception {
//     const char * err () const throw () { 
//         return "Type Error: Card type does not match chain type!"; 
//     }
// } IllegalType;

template <class T>
class Chain : public ChainBase {
protected: 
    string type; // variable to store chain type T
    vector<T*> cardsInChain; // Vector to store cards of Type T belonging to chain<T>
public:
    // Default constructor
    Chain() : ChainBase(false) { // set variable 'base' to false since we create object of type Chain not ChainBase
        T chain_color;
        type = chain_color.getName(); // store chain type 
    };

    // Constructor which accepts an istream and reconstructs the chain from file when a game is resumed.
    Chain(istream& is, CardFactory* cardFactory) : ChainBase(false) { // set variable 'base' to false since we create object of type Chain not ChainBase
        int i = 0;
        string chainName;
        getline(is, chainName, '\t'); // Get text before tab
        char arr[100];
        is.getline(arr, 100);
        while (arr[i] != '\0') {
            Card* c = cardFactory->getCardType(arr[i]); // Retrieve chain type
            if(c != NULL) {
                type = c->getName(); // Set variable type to chain type
                *this += c;
            }
            i++;	
        }
    }

    // Adds a Card to the Chain.
    ChainBase& operator+=(Card* c) {
        if(type == c->getName()) { // If card type is matches chain type then add card to chain
            T* addedCard = new T();
            cardsInChain.push_back(addedCard);
        }
        else throw Card::IllegalType(); //If card type does not match chain type throw exception
        return *this;
    }

    // Counts the number cards in the current chain and returns the number coins
    int sell()  {
        T chain;
        for (int numCoins=4; numCoins>0; numCoins--) {
            if (cardsInChain.size() >= chain.getCardsPerCoin(numCoins)) return numCoins; // Return max number of coins possible from trading in all cards in chain
        }
        return 0; // If not enough cards for at least 1 coin then return 0 coins
    }

    void print(ostream& o) {
        o << cardsInChain.front()->getName() << '\t'; // Print chain type
        for(Card *card : cardsInChain ) { card->print(o); o << " "; }
    }
};
#endif
