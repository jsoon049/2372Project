#include "card.h"
#include "cardFactory.h"

class ChainBase {
protected:
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
};
