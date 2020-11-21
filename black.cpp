#include "Card.h"

class black : public Card {

public:
	const static int TOTALINDECK = 10;

    //pass in the num of coins and return the number of cards needed
	int getCardsPerCoin(int coins) {
		if (coins == 1)
			return 2;
        else if (coins == 2){
            return 4;
        }
        else if (coins == 3){
            return 5;
        }
        else if (coins == 4){
            return 6;
        }
        //coins < 1
		return 0;
	}

	string getName() {
		return "black";
	}

	void print(ostream& out) const {
		out << "b";
	}
};