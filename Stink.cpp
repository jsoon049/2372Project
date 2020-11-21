#include "Card.h"

class Stink : public Card {

public:
	const static int TOTALINDECK = 16;

    //pass in the num of coins and return the number of cards needed
	int getCardsPerCoin(int coins) {
		if (coins == 1)
			return 3;
        else if (coins == 2){
            return 5;
        }
        else if (coins == 3){
            return 7;
        }
        else if (coins == 4){
            return 8;
        }
        //coins < 1
		return 0;
	}

	string getName() {
		return "Stink";
	}

	void print(ostream& out) const {
		out << "S";
	}
};