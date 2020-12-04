#ifndef table_h
#define table_h
#include "player.h"
#include "deck.h"
#include "discardPile.h"
#include "tradeArea.h"

class Table {
protected:
 	Player p1;
	Player p2;
    Deck deck;
    DiscardPile dPile;
    TradeArea tArea; 
public:
	//Table(Player _p1, Player _p2, Deck _d, DiscardPile _dp, TradeArea _ta); // Testing?
    Table(){};
    Table(istream&, CardFactory*);
    bool win(string&) const;
	void printHand(bool);
    friend ostream& operator<<( ostream&, Table&);
	//Helper function//
	void printAll(ostream&);
};
#endif