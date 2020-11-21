#include "Card.h"

class Green : public Card {

public:
	const static int TOTALINDECK = 14;

    //pass in the num of coins and return the number of cards needed
	int getCardsPerCoin(int coins) {
		if (coins == 1)
			return 3;
        else if (coins == 2){
            return 5;
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
		return "Green";
	}

	void print(ostream& out) const {
		out << "G";
	}
};