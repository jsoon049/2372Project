#include "player.h"
#include "discardPile.cpp" // Include this file because discardPile.cpp has include statement for cardFactory.cpp

class NotEnoughCoins : public exception {
    const char * err () const throw () { 
        return "Error: Not enough coins to buy a 3rd chain!"; 
    }
}NotEnoughCoins;

class MaxChains : public exception {
    const char * err () const throw () { 
        return "Error: Already have max chains!"; 
    }
}MaxChains;

// Constructor that creates a Player with a given name.
Player::Player(const string &name) { playerName = name; }

// Constructor which accepts an istream and reconstructs the Player from file
Player::Player(istream& is, CardFactory* cardfactory):playerChains{} {
    string temp; // Used to store second word of line, which is a colon
    string firstWord; // Stores first word of each line
    string text; // Stores each line
    while(getline(is, text)) { // Extract text until newline is found
        istringstream sBuff(text); // String buffer containing text variable
        while(sBuff >> firstWord) {
            if(firstWord == "Name") { sBuff >> temp >> playerName; break; }
            else if(firstWord == "Coins") { sBuff >> temp >> numCoins; break; }
            else if(firstWord == "Chains") break;
            else if(firstWord == "Hand") {
                sBuff >> temp;
                hand = Hand( sBuff, cardfactory ); break;
            }
            else { // Create chains
                if(firstWord == "Empty") { playerChains.push_back( new ChainBase() ); break; }
                else {
                    playerChains.push_back(getChainType(firstWord, sBuff, cardfactory)); break;
                }
            }
        }
        if(firstWord == "Hand") break;
    }
}

// Get the name of the player.
string Player::getName() const { return playerName; }

// Get the number of coins currently held by the player.
int Player::getNumCoins() const { return numCoins; }

// Add a number of coins
Player& Player::operator+=(int coins) {
    this->numCoins += coins;
    return *this;
}

// Returns either 2 or 3. Default max is 2 but return 3 if player succesfully bought a third chain.
int Player::getMaxNumChains() const { return playerChains.size(); }

// Returns the number of non-zero chains
int Player::getNumChains() const {
    int nonZeroChains = 0;
    for(ChainBase *chain : playerChains ) {
        if(chain->isEmpty() == false) nonZeroChains++; // Check if chain is empty
    }
    return nonZeroChains;
}

// Returns the chain at position i.
ChainBase& Player::operator[](int i) {
    return *(playerChains.at(i)); 
}

// Adds an empty third chain to the player for three coins
void Player::buyThirdChain() {
    if(playerChains.size() == 2 && numCoins >= 3) {
        cout <<"Sucess! You bought a 3rd chain." << endl;
        numCoins = numCoins-3;
        playerChains.push_back(new ChainBase()); // Push empty Chain to end of chain vector
    }
    else if(numCoins < 3) throw NotEnoughCoins; // Throw exception if player does not have enough coins
    else if(playerChains.size() == 3) throw MaxChains; // Throw exception if player already has 3 chains
}

// Prints the top card of the player's hand (with argument false) or all of the player's hand (with argument true)
void Player::printHand(ostream& out, bool topOrAll) {  
    if(topOrAll == false) hand.top()->print(out);
    else out << hand; 
}

// Insertion operator (friend) to print a Player to an std::ostream.
ostream& operator<<(ostream& out, const Player& p) {
    out << "Name : " << p.playerName << endl; // Print player name
    out << "Coins : " << p.numCoins << endl; // Print number of coins player has
    out << "Chains : " << endl;
    int i = 0;
    for(auto iter = p.playerChains.begin(); iter != p.playerChains.end(); iter++) {  
        out << *(*iter) << endl; i++; // Print player's chains including empty chains
    }
    return out;
}

//**HELPER FUNCTIONS**//

// Returns reconstructed chain. Used as helper function in istream constructor
ChainBase* Player::getChainType(const string cType, istream& is, CardFactory* cardfactory) {
    if(cType == "black") return new Chain<black>(is, cardfactory);
    else if(cType == "Blue") return new Chain<Blue>(is, cardfactory);
    else if(cType == "Chili") return new Chain<Chili>(is, cardfactory);
    else if(cType == "garden") return new Chain<garden>(is, cardfactory);
    else if(cType == "Green") return new Chain<Green>(is, cardfactory);
    else if(cType == "Red") return new Chain<Red>(is, cardfactory);
    else if(cType == "soy") return new Chain<soy>(is, cardfactory);
    else if(cType == "Stink") return new Chain<Stink>( is, cardfactory);
    else return new ChainBase(true);
}

// Creates a chain at position i and adds the first card of type T to newly created chain<T>
void Player::addChain(const int pos, Card* firstCard) {
    delete playerChains[pos]; // Delete empty chain
    string chainType = firstCard->getName(); // Get chain type
    ChainBase* chain;
    if(chainType == "black" ) chain = new Chain<black>();
    else if(chainType == "Blue" ) chain = new Chain<Blue>();
    else if(chainType == "Chili" ) chain = new Chain<Chili>();
    else if(chainType == "garden" ) chain = new Chain<garden>();
    else if(chainType == "Green" ) chain = new Chain<Green>();
    else if(chainType == "Red" ) chain = new Chain<Red>();
    else if(chainType == "soy" ) chain = new Chain<soy>();
    else chain = new Chain<Stink>();
    *chain += firstCard;  // add card to new chain
    playerChains[pos] = chain;
}
