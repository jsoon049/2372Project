#include "player.h"
#include "discardPile.cpp" // Include this file because discardPile.cpp has include statement for cardFactory.cpp

// constructor
Player::Player(const string& _name) : playerName( _name ) {}

// constructor which accepts an istream and reconstructs the Player from file
Player::Player(istream& is, CardFactory* cardfactory) : playerChains{} {
    string temp, token, line;
    while(getline(is, line)) { // lines containing chain and hand
        cout << line << endl;
        istringstream streamLine(line);
        while( streamLine >> token ) {
            // if Name is read, store into playerName
            if( token == "Name" ) {
                streamLine >> temp >> playerName; break;
            }
            // if Coin(s) is read, store into numCoins
            else if( token == "Coins" ) {
                streamLine >> temp >> numCoins; break;
            }
            else if( token == "Chains" ) break;
            // if Hand is read, build Hand with streamLine
            else if( token == "Hand" ) {
                streamLine >> temp; // should store ":"
                hand = Hand( streamLine, cardfactory ); break;
            }
            // else Chain<T> is read
            else {
                streamLine >> temp;
                if(token == "Empty") {
                    playerChains.push_back( new ChainBase() ); break;
                }
                else {
                    streamLine >> token;
                    //streamLine >> temp; // should store ":"
                    playerChains.push_back( getChainType( token, streamLine, cardfactory ) ); break;
                }
            }
        }
        if( token == "Hand" ) break;
    }
}

// return the name of the player
string Player::getName() const { return playerName; }

// return the amount of coins a player has
int Player::getNumCoins() const { return numCoins; }

// add coins to a player
Player& Player::operator+=(int _coin)
{
    this->numCoins += _coin;
    return *this;
}

// get the max number of chains
int Player::getMaxNumChains() const { return playerChains.size(); }

// Get the number of chains a player has that are NOT empty
int Player::getNumChains() const {
    int numChains = 0;
    for( auto chainRef : playerChains ) {
        if( !chainRef->isEmpty() ) ++numChains;
    }
    return numChains;
}

// Return chain at position i.
// Vector throws out_of_bounds exception if invalid index is given.
ChainBase& Player::operator[](int i) {
    return *( playerChains.at(i) );
}

// buy a third chain if possible
void Player::buyThirdChain() {
    if( numCoins >= 3 && playerChains.size() == 2 ) {
        numCoins -=3;
        playerChains.push_back( new ChainBase() ); // push empty Chain to playerChains
        cout << this->playerName << " has bought their 3rd chain!" << endl;
    }
    else if(numCoins < 3) {
        cout << "ERROR : Not enough coins to buy the chain!" << endl;
    }
    else if (playerChains.size() == 3) {
        cout << "ERROR : You already have 3 chains!" << endl;
    }
}

// print top card or full hand of player
void Player::printHand(ostream& _os,  bool fullHand ) {  
    if( !fullHand ) {
        Card* topCard = hand.top();
        topCard->print( _os );
    }
    else { // prints all of hand
        _os << hand;
    }
}

/*
 *  Insertion operator to print a Player to an ostream.
 *  The player's name, the number of coins in the player's possession and each
 *  of the chains (2 or 3, some possibly empty) should be printed. Note that the
 *  Hand is printed with a separate function above.
 */
ostream& operator<<(ostream& _os, const Player& _p) {
    _os << "Name : " << _p.playerName << endl; // print name
    _os << "Coins : " << _p.numCoins << endl; // print coins
    // print chains
    _os << "Chains" << endl;
    int i = 0;
    for( auto iter = _p.playerChains.begin(); iter != _p.playerChains.end(); ++iter ) {
         _os << i << " - " << *(*iter) << endl; ++i; // print Chains and their indexes
    }
    return _os;
}

// starts a Chain at given index i
void Player::addChain(const int i, Card* _card) {
    // delete empty ChainBase
    delete playerChains[i];
    // get Chain type
    string type = _card->getName();
    // return Chain template
    ChainBase* newChain;
    if( type == "black" ) newChain = new Chain<black>();
    else if( type == "Blue" ) newChain = new Chain<Blue>();
    else if( type == "Chili" ) newChain = new Chain<Chili>();
    else if( type == "garden" ) newChain = new Chain<garden>();
    else if( type == "Green" ) newChain = new Chain<Green>();
    else if( type == "Red" ) newChain = new Chain<Red>();
    else if( type == "soy" ) newChain = new Chain<soy>();
    else newChain = new Chain<Stink>();
    // add Card to returning Chain template
    (*newChain) += _card;
    playerChains[i] = newChain;
}

// getter for Chain template istream constructor
ChainBase* Player::getChainType(const string chainType, istream& is, CardFactory* cardfactory) {
    if(chainType == "black") return new Chain<black>(is, cardfactory);
    else if(chainType == "Blue") return new Chain<Blue>(is, cardfactory);
    else if(chainType == "Chili") return new Chain<Chili>(is, cardfactory);
    else if(chainType == "garden") return new Chain<garden>(is, cardfactory);
    else if(chainType == "Green") return new Chain<Green>(is, cardfactory);
    else if(chainType == "Red") return new Chain<Red>(is, cardfactory);
    else if(chainType == "soy") return new Chain<soy>(is, cardfactory);
    else if(chainType == "Stink") return new Chain<Stink>( is, cardfactory);
    else return new ChainBase(true);
}
