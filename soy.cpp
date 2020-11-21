#include "Card.h"

class soy : public Card {

public:
	const static int TOTALINDECK = 12;

    //pass in the num of coins and return the number of cards needed
	int getCardsPerCoin(int coins) {
		if (coins == 1)
			return 2;
        else if (coins == 2){
            return 4;
        }
        else if (coins == 3){
            return 6;
        }
        else if (coins == 4){
            return 7;
        }
        //coins < 1
		return 0;
	}

	string getName() {
		return "soy";
	}

	void print(ostream& out) const {
		out << "s";
	}
};