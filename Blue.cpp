#include "Card.h"

class Blue : public Card {

public:
	const static int TOTALINDECK = 20;

    //pass in the num of coins and return the number of cards needed
	int getCardsPerCoin(int coins) {
		if (coins == 1)
			return 4;
        else if (coins == 2){
            return 6;
        }
        else if (coins == 3){
            return 8;
        }
        else if (coins == 4){
            return 10;
        }
        //coins < 1
		return 0;
	}

	string getName() {
		return "Blue";
	}

	void print(ostream& out) const {
		out << "B";
	}
};