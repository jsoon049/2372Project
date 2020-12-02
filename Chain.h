#ifndef chain_h
#define chain_h

#include <stdio.h>
#include <vector>
#include "chainBase.h"

template <class T> class Chain : public ChainBase, public vector<T*> {
public:
	// default constructor 
	Chain();
	Chain(istream&, CardFactory*);
	Chain<T>& operator+= (Card* card);
	int sell();
	friend ostream & operator << (ostream & sortie, Chain<T> c) {
		//sortie << c.getType() << '\t';
        sortie << c.type << '\t';
		//if (c.getSize() > 0) {
        if (c.size() > 0) {
			//for (int i = 0; i< c.getSize(); i++)
            for (int i = 0; i< c.size(); i++)
                sortie << c.type.at(0);
		}
		return sortie;
	};
	//void addCard(Card* );
	//string getType();
protected:
	string type;
	void print(ostream& os) const {
		os << (*this);
	};
};

struct IllegalType : public exception {
	const char * err () const throw () { 
		return "Type Error: Card type does not match chain type!"; 
	}
};


template<class T>
inline Chain<T>::Chain() {
	T temp;
	type = temp.getName();
}

template<class T>
Chain<T>::Chain(istream & in , CardFactory * cf) {
    int i = 0;
	string chainTitle;
	getline(in, chainTitle, '\t');
	char type[256];
	in.getline(type, 256);
	// while (type != NULL) {
	// 	if (type != ' ') {
	// 		Card* cardToAdd = ((*cf).getCardType(type));
	// 		(*this).push_back(cardToAdd);
	// 	}															
	// }

}

template<class T>
Chain<T>& Chain<T>::operator+=(Card* card) {
    if(type.compare((*card).getName()) == 0){
		T* temp = new T();
		this->push_back(temp);
	}
	else throw IllegalType();
	return *this;
}


template<class T>
int Chain<T>::sell()
{
	T temp;
	for (int cns = 4; cns > 0; cns--) {
        if (this->size() >= temp.getCardsPerCoin(cns)) return cns;
	}
	return 0;
}

// template<class T>
// void Chain<T>::addCard(Card * card)
// {
// 	(*this) += card;
// }


// template<class T>
// inline string Chain<T>::getType()
// {
// 	return type;
// }

#endif 
