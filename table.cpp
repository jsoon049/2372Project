#include "table.h"
#include "player.cpp"

// // Used for testing
// Table::Table(Player _p1, Player _p2, Deck _d, DiscardPile _dp, TradeArea _ta) { 
//     p1 = _p1;
//     p2 = _p2;
//     deck = _d;
//     dPile = _dp;
//     tArea = _ta;
// }

// Constructor which accepts an istream and reconstruct the Table from file.
Table::Table(istream& in, CardFactory* cardfactory) {
    string firstWord; // Stores first firstWord of each line
    string text; // Stores each line
    string temp; // Used to store second word of line, which is a colon
    while(getline(in, text)) { // Extract text until newline is found
        istringstream sBuff(text); // String buffer containing text variable
        while(sBuff >> firstWord) {
            if(firstWord == "Player1") { p1 = *new Player(in, cardfactory); break; }
            if(firstWord == "Player2") { p2 = *new Player(in, cardfactory); break; }
            if(firstWord == "DiscardPile") {
                sBuff >> temp;
                dPile = DiscardPile( sBuff, cardfactory);
                break;
            }
            if(firstWord == "TradeArea") {
                sBuff >> temp;
                tArea = TradeArea( sBuff, cardfactory);
                break;
            }
            if(firstWord == "Deck") {
                sBuff >> temp;
                deck = Deck(sBuff, cardfactory);
                break;
            }
            //if(firstWord == "done") break; // Signifies end of file
        }
        //if(firstWord == "done") break;
    }
}

// Returns true when a player has won. The name of the player is returned by reference (in the argument).
bool Table::win(string& winner) const {   
    if(deck.empty()) { // Deck must be empty before a player can win
        int coins1 = p1.getNumCoins();
        int coins2 = p2.getNumCoins();
        if(coins1 == coins2) winner = "Tie"; // Tie game
        else if(coins1 > coins2) winner = p1.getName(); // Player1 won
        else winner = p2.getName(); // Player2 won
        return true;
    }
    return false; // If deck is not empty yet then game isn't over so no winner yet
}

// Prints the top card of the player's hand (with argument false) or all of the player's hand (with argument true).
void Table::printHand(bool topOrAll) {  
    if(topOrAll == false) {
        p1.hand.top()->print(cout);
        p2.hand.top()->print(cout);
    }
    else {
        cout << p1.hand << endl;
        cout << p2.hand << endl;
    }; 
}

// Insertion operator (friend) to print a Table to an std::ostream
ostream& operator<<(ostream& out, Table& _table) {
    out << "Player 1" << endl << _table.p1 << endl;  // Print player1 info (hand content not printed)
    out << "Player 2" << endl << _table.p2 << endl;  // Print player2 info (hand content not printed))
    out << "Discard Pile: " << _table.dPile << endl; // Print only top card of discard pile
    out << "Trading Area: " << _table.tArea << endl; // Print trade area
    return out;
}

/*
 *  prints the following to file as an example
 *  Player1
 *  Name: Adam
 *  Coin(s): 4
 *  Chains
 *  0 -  Malachite : M M M M M
 *  1 - Amethyst : A A
 *  Hand : A M Q R T R
 *
 *  Player2
 *  Name: Betty
 *  Coin(s): 7
 *  Chains
 *  0 - Ruby : R R R R
 *  1 - Quartz : Q Q Q Q Q Q Q
 *  2 - Obsidian : O O O O O
 *  Hand : M A T T A M

 *  TradeArea : O E A E E A O O A O O E E A A A A O
 *  DiscardPile : A O Q T R M M T Q O E H Q T E M A
 *  Deck : etc...
 *  end
 */
void Table::printAll(ostream& out) {
    out << "Player1 " << endl << p1; // Print player1 info
    out << "Hand : "; p1.printHand(out, true); out << endl << endl; // Print all cards in player1 hand 
    out << "Player2 " << endl << p2; // Print player2 info
    out << "Hand : "; p2.printHand(out, true); out << endl << endl; // Print all cards in player2 hand 
    out << "DiscardPile : "; dPile.print(out); // Print all cards in discardPile
    out << "TradeArea : " << tArea << endl; // Print all cards in tradeArea
    out << "Deck : " << deck << endl; // Print all cards in deck
    //out << "done"; // Print done to show end of file
}