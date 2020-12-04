//GOOD VERSION DO NOT TOUCH//
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>

#include "hand.cpp"
#include "tradeArea.cpp"
#include "table.cpp"

// Function used to save game to a pre-specifiec .txt file
void pauseSave(Table& t) {
    string ans;
    while(true) {
        cout << "Do you want to pause and save the game?" << endl;
        cin >> ans;
        cout << endl;
        if(ans == "No" || ans == "no") break;
        if(ans == "Yes" || ans == "yes") {
            ofstream outFile("savedGame300016044_300018781.txt"); // Open file
            t.printAll(outFile); // Print full table to file
            outFile.close(); // Close file
            exit(0);
        }
        else cout << "Please type yes or no" << endl;
    }
}

// Function used to load saved game file from pre-specified file. Returns table with loaded info
Table* loadFromSave (CardFactory *cf) {
    ifstream inFile("savedGame300016044_300018781.txt"); // Open file
    if (inFile.is_open()) {
		Table* table = new Table(inFile, cf); // Load table from file
		return table;
	}
	else return NULL;
}

// Add card to specified chain
void addCardToChain(Player& p, Table& table, int index, Card* cardToChain) {
    while(index < 0 || index >= p.getMaxNumChains()) {
        if(p.getMaxNumChains() == 2) {
            cout << "You currently own two chains." << endl;
            cout << "Enter chain number that you want to add " << cardToChain->getName() << " bean to. (Choices are 0,1)" << endl;
        }
        else {
            cout << "You currently own three chains." << endl;
            cout << "Enter chain number that you want to add " << cardToChain->getName() << " bean to. (Choices are 0,1,2)" << endl;
        }
        cin >> index;
        while (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(p.getMaxNumChains() == 2) {
                cout << "You currently own two chains." << endl;
                cout << "Enter chain number that you want to add " << cardToChain->getName() << " bean to. (Choices are 0,1)" << endl;
            }
            else {
                cout << "You currently own three chains." << endl;
                cout << "Enter chain number that you want to add " << cardToChain->getName() << " bean to. (Choices are 0,1,2)" << endl;
            }
            cin >> index;
        }
    }
    ChainBase* chain = &p[index];
    if(chain->isEmpty()) p.addChain(index, cardToChain);
    else{
        try{ *chain += (cardToChain); }
        catch(Card::IllegalType &e) {
            string ans;
            cout << "Card types do not match, would you like to sell this chain and replace it with new card or try another chain? (yes to sell or no to try another chain)" << endl;
            cin >> ans;
            if(ans == "yes" || ans == "Yes") {
                int coinsEarned = chain->sell();
                cout << "You earned " << coinsEarned << " coins from selling chain" << index+1 << endl;
                p+=coinsEarned;
                p.addChain(index, cardToChain);
            }
            else{addCardToChain(p, table, -1, cardToChain); }
        }
    }
}

int main(void) {
    Player plOne; // Player object for player one
    string plOneName; // String to store player one's name
    Player plTwo; // Player object for player two
    string plTwoName; // String to store player two's name
    Player players[2];
    string ans; // Used to store user's anss when prompted										
    CardFactory *cf = CardFactory::getFactory(); // Retrieve single instance of CardFactory
    Table* gameTable; // Pointer to table object
    int playerTurn = 1; // Num that tells us which player's move it is. 1 = player1's move and 2 = player2's move
    string winner = ""; // Stores player's name that won the game								
    Card* cardToChain;
    int position = 1; // Used for arbitrary position for discarding

    // Ask user if they want to create game or load saved game from file
    while(true) {
        cout << "Enter 1 to create a new game or 2 to load a saved game from file?" << endl;
        cin >> ans;     
        if(ans == "1") { break; }
        else if(ans == "2") { break; }
        else cout << "Invalid input! Try again." << endl;
    }

    // Create new game
    if(ans == "1") {
		gameTable = new Table();
        // Create player1
        while (true) {
            cout << "Enter name for player1" << endl;
            cin >> plOneName;
            if(plOneName == "") cout << "Invalid input! Try again." << endl;
            else break;
        }
		players[0] = Player(plOneName); // Create player1 object
		gameTable->p1 = players[0];
        // Create player2
        while (true) {
            cout << "Enter name for player2" << endl;
            cin >> plTwoName;
            if(plTwoName == "") cout << "Invalid input! Try again." << endl;
            else break;
        }
		players[1] = Player(plTwoName); // Create player2 object
		gameTable->p2 = players[1];
		gameTable->deck = cf->getDeck(); // Retrieve shuffled deck
        // Each player draws 5 cards to their hand to start
        for(int i = 0; i < 5; ++i) {
            gameTable->p1.hand+=(gameTable->deck.draw());
            gameTable->p2.hand+=(gameTable->deck.draw());
        }
    }
    else gameTable = loadFromSave(cf->getFactory()); // Load paused game from file.
    
    // Start game
    while(!gameTable->win(winner)) {
        cout << endl << "**Table Below**" << endl;
        cout << *gameTable;
        cout << "**End of Table**" << endl << endl;
        pauseSave(*gameTable); // If pause, save game to file and exit

        if(playerTurn == 1) { //Player1 turn
            cout << "It's " << gameTable->p1.getName() << "'s turn!" << endl;
            // If possible ask user if they want to buy third chain
            if((gameTable->p1.getNumCoins() >= 3) && (gameTable->p1.getMaxNumChains()<3)) {
                while(true){
                    cout << "Do you want to buy a third chain? (yes or no) " << endl;
                    cin >> ans;
                    if(ans == "yes") { gameTable->p1.buyThirdChain(); break; }
                    if(ans == "no") break;
                }
            }

            // Player draws top card from Deck
            Card* topCard = gameTable->deck.draw();
            cout << "You draw a " + topCard->getName() << " bean from the top of the deck." << endl;
            gameTable->p1.hand.operator+=(topCard);
            cout << "Current hand: ";
            gameTable->p1.printHand(cout, true);
            cout << endl;
            
            // If TradeArea is not empty
            if(gameTable->tArea.numCards()!=0) {
                // Loop through all cards in tradeArea
                for(auto itr = gameTable->tArea.cardTypes.begin(); itr != gameTable->tArea.cardTypes.end(); itr = gameTable->tArea.cardTypes.erase(itr)) {
                    Card* chainOrDiscard = gameTable->tArea.trade(*itr);
                    if(chainOrDiscard != nullptr) {
                        cout << "Do you want to add " << *itr << " bean from trade area to a chain? (yes or no)" << endl;
                        cin >> ans;
                        // If yes add all cards of bean type T to chain
                        while(true) {
                            if(ans == "yes" || ans == "Yes") { 
                                addCardToChain(gameTable->p1, *gameTable, -1, chainOrDiscard); 
                                break;
                            }
                            else if(ans == "no" || ans == "No") {
                                cout << "Discarding " << chainOrDiscard->getName() << " bean from tradeArea" << endl;
                                gameTable->dPile += chainOrDiscard; // If no discard all cards in trade area of type T
                                break;
                            }
                        }
                    }
                }
            }
            cout << endl;

            // Play topmost card
            cout << "Playing top card: ";
            gameTable->p1.printHand(cout ,false); // Print top card
            cout << " from hand" << endl;
            cardToChain = gameTable->p1.hand.play(); // Remove top card from player's hand
            addCardToChain(gameTable->p1, *gameTable, -1, cardToChain);

            // If player wants they can play the now topmost card from Hand.
            cout << "New Top card in hand: ";
            gameTable->p1.printHand(cout, false);
            cout << endl;
            cout << "Do you want to add this new top card to a chain? (yes or no)" << endl;
            cin >> ans;
            while(true){
                if(ans == "yes" || ans == "Yes") {
                    cardToChain = gameTable->p1.hand.play();
                    addCardToChain(gameTable->p1, *gameTable, -1, cardToChain);
                    break;
                }
                if(ans == "no" || ans == "No") break;
            }

            // If player decides to show the player's full hand they can select an arbitrary card
            // and discard it from the player's hand and place it on the discard pile.
            cout << "If you show your hand you can discard one arbitrary card from it to the discard pile." << endl;
            cout << "Do you want to do that? (yes or no)" << endl;
            cin >> ans;
            if(ans == "yes" || ans == "Yes") {
                cout << "Current hand: ";
                gameTable->p1.printHand(cout, true); cout << endl;
                while(gameTable->p1.hand.hand.empty() == false) {
                    position = rand() % (gameTable->p1.hand.hand.size()-1);
                    Card* discardCard = gameTable->p1.hand[position];
                    if(discardCard == nullptr) position = 0;
                    else if(discardCard != nullptr) {
                        cout << "Discarding " << discardCard->getName() << " bean from hand" << endl;
                        gameTable->dPile += discardCard;
                        cout << "Your hand after discard: "; 
                        gameTable->p1.printHand(cout, true); 
                        cout << endl;
                        break;
                    }
                }
            }

            // Draw three cards from the deck and place cards in the trade area
            cout << "Drawing three cards from deck and placing them in trade area" << endl;
            for(int i = 0; i < 3; i++) {
                if(!(gameTable->deck.empty())) gameTable->tArea+=(gameTable->deck.draw());
            }

            // While top card of discard pile matches an existing card in the trade area
            while(gameTable->dPile.top() != nullptr && gameTable->tArea.legal(gameTable->dPile.top())) {
                cout << "Top card of discard pile matches an existing card in the trade area. ";
                cout << "So we draw the top-most card from the discard pile and place it in the trade area" << endl;
                gameTable->tArea += (gameTable->dPile.pickUp()); // Draw the top-most card from the discard pile and place it in the trade area
            }
            cout << "Trade Area: "; 
            cout << (gameTable->tArea) << endl;

            // While the trade area is not empty
            if(gameTable->tArea.numCards() != 0) {
                for(auto itr = gameTable->tArea.cardTypes.begin(); itr != gameTable->tArea.cardTypes.end();) {
                    while(true){
                        cout << "Do you want to add " << *itr << " from trade area to one of your chains? (yes or no)" << endl; // Ask a user if they want to add each card to your chain,
                        cin >> ans;
                        if(ans == "yes" || ans == "Yes") {
                            Card* chainOrDiscard = gameTable->tArea.trade(*itr);
                            if(chainOrDiscard != nullptr) {
                                addCardToChain(gameTable->p1, *gameTable, -1, chainOrDiscard);
                                chainOrDiscard = gameTable->tArea.trade(*itr);
                            }
                            gameTable->tArea.cardTypes.erase(itr);       
                            break;
                        }
                        if(ans == "no" || ans == "No") break;
                    }
                    ++itr;
                    //else ++itr; // If user doesn't want to add card to chain then leave it for the next player.
                }
            }

            // Draw two cards from Deck and add the cards to the player's hand (at the back).
            if(!gameTable->deck.empty()) {
                cout << "Before ending your turn you draw 2 cards" << endl;
                Card *temp = gameTable->deck.draw();
                gameTable->p1.hand += temp;
                cout << "You drew a " << temp->getName() << " bean" << endl;
                temp = gameTable->deck.draw();
                gameTable->p1.hand += temp;
                cout << "You drew a " << temp->getName() << " bean" << endl;
            }
            playerTurn = 2;
        }

        //**PLAYER 2 TURN**//
        cout << endl << "**Table Below**" << endl;
        cout << *gameTable;
        cout << "**End of Table**" << endl << endl;
        if(playerTurn == 2) { //Player2 turn
            cout << "It is " << gameTable->p2.getName() << "'s turn!" << endl;
            // If possible ask user if they want to buy third chain
            if((gameTable->p2.getNumCoins() >= 3) && (gameTable->p2.getMaxNumChains()<3)) {
                while(true){
                    cout << "Do you want to buy a third chain? (yes or no) " << endl;
                    cin >> ans;
                    if(ans == "yes") { gameTable->p2.buyThirdChain(); break; }
                    if(ans == "no") break;
                }
            }

            // Player draws top card from Deck
            Card* topCard = gameTable->deck.draw();
            cout << "You draw a " + topCard->getName() << " bean from the top of the deck." << endl;
            gameTable->p2.hand.operator+=(topCard);
            cout << "Current hand: ";
            gameTable->p2.printHand(cout, true);
            cout << endl;
             
            // If TradeArea is not empty
            if(gameTable->tArea.numCards()!=0) {
                // Loop through all cards in tradeArea
                for(auto itr = gameTable->tArea.cardTypes.begin(); itr != gameTable->tArea.cardTypes.end(); itr = gameTable->tArea.cardTypes.erase(itr)) {
                    cout << "Do you want to add " << *itr << " bean from trade area to a chain? (yes or no)" << endl;
                    cin >> ans;
                    Card* chainOrDiscard = gameTable->tArea.trade(*itr);
                    if(chainOrDiscard != nullptr) {
                        // If yes add all cards of bean type T to chain
                        if(ans == "yes" || ans == "Yes") addCardToChain(gameTable->p2, *gameTable, -1, chainOrDiscard);
                        else {
                            cout << "Discarding " << chainOrDiscard->getName() << " bean from tradeArea" << endl;
                            gameTable->dPile += chainOrDiscard; // If no discard all cards in trade area of type T
                        }
                    }
                }
            }

            // Play topmost card
            cout << endl << "Playing top card: ";
            gameTable->p2.printHand(cout ,false); // Print top card
            cout << " from hand" << endl;
            cardToChain = gameTable->p2.hand.play(); // Remove top card from player's hand
            addCardToChain(gameTable->p2, *gameTable, -1, cardToChain);

            // If player wants they can play the now topmost card from Hand.
            cout << "New Top card in hand: ";
            gameTable->p2.printHand(cout, false);
            cout << endl;
            cout << "Do you want to add this new top card to a chain? (yes or no)" << endl;
            cin >> ans;
            if(ans == "yes" || ans == "Yes") {
                cardToChain = gameTable->p2.hand.play();
                addCardToChain(gameTable->p2, *gameTable, -1, cardToChain);
            }

            // If player decides to show the player's full hand they can select an arbitrary card
            // and discard it from the player's hand and place it on the discard pile.
            cout << "If you show your hand you can discard one arbitrary card from it to the discard pile." << endl;
            cout << "Would you like to do that? (yes or no)" << endl;
            cin >> ans;
            if(ans == "yes" || ans == "Yes") {
                cout << "Current hand: ";
                gameTable->p2.printHand(cout, true); cout << endl;
                while(gameTable->p2.hand.hand.empty() == false) {
                    position = rand() % (gameTable->p2.hand.hand.size()-1);
                    Card* discardCard = gameTable->p2.hand[position];
                    if(discardCard == nullptr) position = 0;
                    else if(discardCard != nullptr) {
                        cout << "Discarding " << discardCard->getName() << " bean from hand" << endl;
                        gameTable->dPile += discardCard;
                        cout << "Your hand after discard: "; 
                        gameTable->p2.printHand(cout, true); 
                        cout << endl;
                        break;
                    }
                }
            }

            // Draw three cards from the deck and place cards in the trade area
            cout << "Drawing three cards from deck and placing them in trade area" << endl;
            for(int i = 0; i < 3; i++) {
                if(!gameTable->deck.empty()) gameTable->tArea+=(gameTable->deck.draw());
            }

            // While top card of discard pile matches an existing card in the trade area
            while(gameTable->dPile.top() != nullptr && gameTable->tArea.legal(gameTable->dPile.top())) {
                cout << "Top card of discard pile matches an existing card in the trade area. ";
                cout << "So we draw the top-most card from the discard pile and place it in the trade area" << endl;
                gameTable->tArea += (gameTable->dPile.pickUp()); // Draw the top-most card from the discard pile and place it in the trade area
            }
            cout << "Trade Area: "; cout << gameTable->tArea << endl;

            // While the trade area is not empty
            if(gameTable->tArea.numCards() != 0) {
                for(auto itr = gameTable->tArea.cardTypes.begin(); itr != gameTable->tArea.cardTypes.end();) {
                    while(true){
                        cout << "Do you want to add " << *itr << " from trade area to one of your chains? (yes or no)" << endl; // Ask a user if they want to add each card to your chain,
                        cin >> ans;
                        if(ans == "yes" || ans == "Yes") {
                            Card* chainOrDiscard = gameTable->tArea.trade(*itr);
                            if(chainOrDiscard != nullptr) {
                                addCardToChain(gameTable->p2, *gameTable, -1, chainOrDiscard);
                                chainOrDiscard = gameTable->tArea.trade(*itr);
                            }
                            gameTable->tArea.cardTypes.erase(itr);       
                            break;
                        }
                        if(ans == "no" || ans == "No") break;
                    }
                    ++itr;
                    //else ++itr; // If user doesn't want to add card to chain then leave it for the next player.
                }
            }

            // Draw two cards from Deck and add the cards to the player's hand (at the back).
            if(!gameTable->deck.empty()) {
                cout << "Before ending your turn you draw 2 cards" << endl;
                Card *temp = gameTable->deck.draw();
                gameTable->p2.hand += temp;
                cout << "You drew a " << temp->getName() << " bean" << endl;
                temp = gameTable->deck.draw();
                gameTable->p2.hand += temp;
                cout << "You drew a " << temp->getName() << " bean" << endl;
            }
            playerTurn = 1;
        }
    }

	if (winner == "Tie") cout << "It's a TIE!" << endl;
	else cout << "Congratulations " << winner << ". You're the winner!" << endl;
	delete gameTable;
    delete cf;
	return 0;
}
