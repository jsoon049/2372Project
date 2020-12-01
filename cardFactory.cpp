#include "cardFactory.h"
#include "card.cpp"
#include "deck.cpp"
 
// Constructor used to create all the cards
CardFactory::CardFactory() { 		
	Card * newCard;
	deck = new Deck();
	for (int i = 0; i < 10; i++) { 
		newCard = new black();   
		deck->push_back(newCard);
	}
	for (int i = 0; i < 20; i++) {
		newCard = new Blue();
		deck->push_back(newCard);
	}
	for (int i = 0; i < 18; i++) {
		newCard = new Chili();
		deck->push_back(newCard);
	}
	for (int i = 0; i < 6; i++) {
		newCard = new garden();
		deck->push_back(newCard);
	}
	for (int i = 0; i < 14; i++) {
		newCard = new Green();
		deck->push_back(newCard);
	}
	for (int i = 0; i < 8; i++) {
		newCard = new Red();
		deck->push_back(newCard);
	}
	for (int i = 0; i < 12; i++) {
		newCard = new soy();
		deck->push_back(newCard);
	}
	for (int i = 0; i < 16; i++) {
		newCard = new Stink();
		deck->push_back(newCard);
	}
}

// Returns a pointer to the only instance of CardFactory
CardFactory * CardFactory::getFactory() 	
{
	static CardFactory cf; // Create static instance of CardFactory
	return &cf;
}

// Returns a shuffled deck with all 104 bean cards. The deck is shuffled using std::shuffle
Deck CardFactory::getDeck()
{
	unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // obtain a time-based seed -- source: cplusplus.com/reference/algorithm/shuffle/
	shuffle(deck->begin(), deck->end(), default_random_engine(seed));
	return *deck;
}

// **HELPER FUNCTIONS** //
// Helper function used to retrieve a specific card
Card* CardFactory::getCardType(char bean) {		
	Card * card = NULL;
	if (bean == 'b') card = new black();
	else if (bean == 'B') card = new Blue();
	else if (bean ==' C') card = new Chili();
	else if (bean == 'g') card = new garden();
	else if (bean == 'G') card = new Green();
	else if (bean == 'R') card = new Red();
	else if (bean == 's') card = new soy();
	else if (bean == 'S') card = new Stink();
	return card;
}

// Helper function used when we are loading out deck from file
Deck CardFactory::setDeck(istream &in)		
{
	deck = new Deck();
	char cardType[256];
	in.getline(cardType, 256);
	int i = 0;
	while (cardType[i] != NULL) {
		Card* cardToAdd = getCardType(cardType[i]);
		deck->push_back(cardToAdd);									
		i++;
	}
	return *deck;
}