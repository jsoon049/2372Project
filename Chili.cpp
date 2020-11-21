#include "Card.h"

class Chili : public Card {

public:
	const static int TOTALINDECK = 18;

    //pass in the num of coins and return the number of cards needed
	int getCardsPerCoin(int coins) {
		if (coins == 1)
			return 3;
        else if (coins == 2){
            return 6;
        }
        else if (coins == 3){
            return 8;
        }
        else if (coins == 4){
            return 9;
        }
        //coins < 1
		return 0;
	}

	string getName() {
		return "Chili";
	}

	void print(ostream& out) const {
		out << "C";
	}
};