#include "cardFactory.h"
#include "deck.cpp"
#include "card.cpp"
 
// Constructor used to create all the cards
CardFactory::CardFactory() { 		
	Card * card;
	d = new Deck();
	for (int i = 0; i < 10; i++) { 
		card = new black();   
		d->push_back(card);
	}
	for (int i = 0; i < 20; i++) {
		card = new Blue();
		d->push_back(card);
	}
	for (int i = 0; i < 18; i++) {
		card = new Chili();
		d->push_back(card);
	}
	for (int i = 0; i < 6; i++) {
		card = new garden();
		d->push_back(card);
	}
	for (int i = 0; i < 14; i++) {
		card = new Green();
		d->push_back(card);
	}
	for (int i = 0; i < 8; i++) {
		card = new Red();
		d->push_back(card);
	}
	for (int i = 0; i < 12; i++) {
		card = new soy();
		d->push_back(card);
	}
	for (int i = 0; i < 16; i++) {
		card = new Stink();
		d->push_back(card);
	}
}

// Returns a pointer to the only instance of CardFactory
CardFactory * CardFactory::getFactory() {
	static CardFactory cardfactory; // Create static instance of CardFactory
	return &cardfactory;
}

// Returns a shuffled deck with all 104 bean cards. The deck is shuffled using std::shuffle
Deck CardFactory::getDeck() {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // obtain a time-based seed
	shuffle(d->begin(), d->end(), default_random_engine(seed));
	return *d;
}

// **HELPER FUNCTIONS** //
// Helper function used to retrieve a specific card
Card* CardFactory::getCardType(char bean) {		
	Card * card = NULL; 
	if (bean == 'b') card = new black();
	else if (bean == 'B') card = new Blue();
	else if (bean == 'C') card = new Chili();
	else if (bean == 'g') card = new garden();
	else if (bean == 'G') card = new Green();
	else if (bean == 'R') card = new Red();
	else if (bean == 's') card = new soy();
	else if (bean == 'S') card = new Stink();
	return card;
}

// Helper function used when we are loading out deck from file
Deck CardFactory::auxLoadDeck(istream &is) {
	int i = 0;
	d = new Deck();
	char cardType[300]; // array used to stored all cards in deck
	is.getline(cardType, 300);
	while (cardType[i] != '\0') {
		Card* addedCard = getCardType(cardType[i]); // get card type
		if(addedCard != NULL) { // if card exists
			d->push_back(addedCard); // add card to deck						
		}			
		i++;
	}
	return *d;
}