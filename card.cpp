#include "Card.h"

//**black bean class**//
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

//**Blue bean class**//
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

//**Chili bean class**//
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

//**garden bean class**//
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
        //coins < 1 or coins = 1 or coins = 4
		return 0;
	}

	string getName() {
		return "garden";
	}

	void print(ostream& out) const {
		out << "g";
	}
};

//**Green bean class**//
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

//**Red bean class**//
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

//**soy bean class**//
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

//**Stink bean class**//
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