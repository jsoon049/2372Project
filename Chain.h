#ifndef chain_h
#define chain_h

#include <stdio.h>
#include <vector>
#include "chainBase.h"

template <class T> class Chain : public ChainBase, public vector<T*> {
public:
	Chain();
	Chain(istream&, CardFactory*);
	Chain<T>& operator+= (Card* card);
	int sell();
	//Insertion operator (friend) to print Chain on an std::ostream.
	friend ostream & operator << (ostream & os, Chain<T> chain) {
        os << chain.type << '\t'; // print full name of the bean before tab
        if (chain.size() > 0) {
            for (int i = 0; i< chain.size(); i++) os << chain.type.at(0); //print first letter of bean color
		}
		return os;
	};
protected:
	string type; //string variable to store color of chain
	void print(ostream& os) const { os << (*this); };
};

struct IllegalType : public exception {
	const char * err () const throw () { 
		return "Type Error: Card type does not match chain type!"; 
	}
};

//default constructor 
template<class T>
inline Chain<T>::Chain() {
	T chain_color;
	type = chain_color.getName();
}

// Constructor which accepts an istream and reconstructs the chain from file when a game is resumed.
template<class T>
Chain<T>::Chain(istream & is, CardFactory * cardFactory) {
    int i = 0;
	string chainName;
	getline(is, chainName, '\t'); //Get text before tab
	char arr[100];
	is.getline(arr, 100);
	while (arr[i] != '\0') {
		Card* c = cardFactory->getCardType(arr[i]); //Retrieve chain type
		type = c->getName(); //Set variable type to chain type
		*this += c;
		i++;								
	}
}

// Adds a card to the Chain
template<class T>
Chain<T>& Chain<T>::operator+=(Card* card) {
    if(type.compare((*card).getName()) == 0){ // Check if the run-time type matches chain type
		T* addCard = new T();
		this->push_back(addCard); //If types match add card
	}
	else throw IllegalType(); //If types don't match throw exception
	return *this;
}

// Counts the number cards in the current chain and returns the number coins
template<class T>
int Chain<T>::sell()
{
	T chain;
	for (int numCoins=4; numCoins>0; numCoins--) {
        if (this->size() >= chain.getCardsPerCoin(numCoins)) return numCoins;
	}
	return 0;
}
#endif 
