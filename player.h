#ifndef player_h
#define player_h
#include "chain.h"
#include "hand.h"
#include <sstream>

class Player {
protected:
    string playerName;
    int numCoins = 0;
    vector<ChainBase*> playerChains {new ChainBase(), new ChainBase()}; // Vector to hold up to 3 chains for the player.
                                                                          // When player object is created, vector is created with 2 empty chains.
public:
    Hand hand; // Variable containing player's hand
    Player(){}; // Default Constructor
    Player(const string&);
    Player(istream&, CardFactory*);
    string getName() const;
    int getNumCoins() const;
    Player& operator+=(int);
    int getMaxNumChains() const;
    int getNumChains() const;
    ChainBase& operator[](int);
    void buyThirdChain();
    void printHand(ostream&, bool);
    friend ostream& operator<<(ostream&, const Player&);

    //Helper functions
    ChainBase* getChainType(const string, istream&, CardFactory*);
    void addChain(const int, Card*);
};

#endif
