#include "card.h"
#include "cardFactory.h"

class ChainBase {
protected:
	//virtual void addCard(Card*) = 0;
	virtual void print(ostream&) const = 0;
public:
	virtual int sell() = 0;
	friend ostream & operator << (ostream &os, const ChainBase& chain_base) {
		chain_base.print(os);
		return os;
	};
	ChainBase& operator+= (Card* card) {
		*this+=(card);
		return *this;
	};
    //virtual bool legal(Card*) = 0;
	//virtual int getSize() = 0;
	//virtual string getType() = 0;
};

// class Chain_Base;

// //ostream& operator<<( ostream&, const Chain_Base& );

// class Chain_Base {
// protected:
//     bool empty = true; // If derived Chain<T> is created, empty = false
// public:
//     Chain_Base(){}; // default constructor
//     Chain_Base( bool _empty ) : empty(_empty) {}; // constructor with boolean

//     virtual int sell() const { return 0; };
//     // returns this object because Chain<T> has not been initialized
//     virtual Chain_Base& operator+=( Card* _card ) { return *this; };

//     virtual void print( ostream& _os ) const { _os << "Empty"; };
//     bool isEmpty() const { return empty; };

//     // insertion operator using "Virtual Friend Function Idiom"
//     friend ostream& operator<<( ostream& _os, const Chain_Base& _chain )
//     {
//         _chain.print( _os );
//         return _os;
//     };
// };