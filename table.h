#ifndef table_h
#define table_h
#include "player.h"
#include "deck.h"
#include "discardPile.h"
#include "tradeArea.h"

class Table {
public:
	Player p1; // Object for player1
	Player p2; // Object for player2 
    Deck deck; // Object for deck 
    DiscardPile dPile; // Object for discard pile 
    TradeArea tArea; // Object for trade area
    Table(){}; // Default constructor 
    Table(istream&, CardFactory*);
    bool win(string&) const;
	void printHand(bool);
    friend ostream& operator<<( ostream&, Table*);
	void printAll(ostream&); // Helper function //
};
#endif