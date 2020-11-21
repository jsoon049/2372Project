#include "Card.h"

class Red : public Card {

public:
	const static int TOTALINDECK = 8;

    //pass in the num of coins and return the number of cards needed
	int getCardsPerCoin(int coins) {
		if (coins == 1)
			return 2;
        else if (coins == 2){
            return 3;
        }
        else if (coins == 3){
            return 4;
        }
        else if (coins == 4){
            return 5;
        }
        //coins < 1
		return 0;
	}

	string getName() {
		return "Red";
	}

	void print(ostream& out) const {
		out << "R";
	}
};