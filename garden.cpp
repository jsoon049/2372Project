#include "Card.h"

class garden : public Card {

public:
	const static int TOTALINDECK = 6;

    //pass in the num of coins and return the number of cards needed
	int getCardsPerCoin(int coins) {
		if (coins == 2)
			return 2;
        else if (coins == 3){
            return 3;
        }
        //coins < 1
		return 0;
	}

	string getName() {
		return "garden";
	}

	void print(ostream& out) const {
		out << "g";
	}
};