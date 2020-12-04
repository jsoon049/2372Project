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
Table* loadGame (CardFactory *cf) {
    ifstream inFile("savedGame300016044_300018781.txt"); // Open file
    if (inFile.is_open()) {
		Table* table = new Table(inFile, cf);
		return table;
	}
	else return NULL;
}

// Add card to specified chain
void addToChain(Player& p, Table& table, int index, Card* cardToChain) {
    while(index < 0 || index >= p.getMaxNumChains()) {
        cout << "Please choose a chain to add " << cardToChain->getName() << " to. (Choices are 0,1,2)" << endl;
        cin >> index;
    }
    ChainBase* chain = &p[index];
    if(chain->isEmpty()) p.addChain(index, cardToChain);
    else{
        try{ *chain += (cardToChain); }
        catch(Card::IllegalType &e) {
            string answer;
            cout << "Card types do not match, would you like to sell this chain and replace it with new card or try another chain? (yes to sell or no to try another chain)" << endl;
            cin >> answer;
            if(answer == "yes" || answer == "Yes") {
                p+=chain->sell();
                p.addChain(index, cardToChain);
            }else{addToChain(p, table, -1, cardToChain); }
        }
    }
}

int main(void) {
    Player plOne; // Player object for player one
    string plOneName; // String to store player one's name
    Player plTwo; // Player object for player two
    string plTwoName; // String to store player two's name
    Player players[2];
    string answer; // Used to store user's answers when prompted										
    CardFactory *cf = CardFactory::getFactory(); // Retrieve single instance of CardFactory
    int playerTurn = 1; // Num that tells us which player's move it is. 1 = player1's move and 2 = player2's move
    string winner = "";

    int index = -1;									
    Table* gameTable;
    Card* cardToChain;
    //string answer;
    int position;

    // Ask user if they want to create game or load saved game from file
    while(true) {
        cout << "Enter 1 to create a new game or 2 to load a saved game from file?" << endl;
        cin >> answer;     
        if(answer == "1") { break; }
        else if(answer == "2") { break; }
        else cout << "Invalid input! Try again." << endl;
    }

    // Create new game
    if(answer == "1") {
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
    else gameTable = loadGame(cf->getFactory()); // Load paused game from file.
    
    // Start game
    while(!gameTable->win(winner)) {
        cout << endl << "**Table Below**" << endl;
        cout << *gameTable;
        cout << "**End of Table**" << endl << endl;
        pauseSave(*gameTable); // If pause, save game to file and exit

        if(playerTurn == 1) { //Player1 turn
            cout << "It is " << gameTable->p1.getName() << "'s turn!" << endl;
            // If possible ask user if they want to buy third chain
            if((gameTable->p1.getNumCoins() >= 3) && (gameTable->p1.getMaxNumChains()<3)) {
                while(true){
                    cout << "Do you want to buy a third chain? (yes or no) " << endl;
                    cin >> answer;
                    if(answer == "yes") { gameTable->p1.buyThirdChain(); break; }
                    if(answer == "no") break;
                }
            }

            // Player draws top card from Deck
            Card* drawCard = gameTable->deck.draw();
            cout << "You draw a " + drawCard->getName() << " bean from the top of the deck." << endl;
            gameTable->p1.hand.operator+=(drawCard);
            gameTable->p1.printHand(cout, true);
             
            // If TradeArea is not empty
            if(gameTable->tArea.numCards()!=0) {
                // Loop through all cards in tradeArea
                for(auto iter = gameTable->tArea.cardTypes.begin(); iter != gameTable->tArea.cardTypes.end(); iter = gameTable->tArea.cardTypes.erase(iter)) {
                    cout << endl;
                    cout << "Do you want to add " << *iter << " bean to a chain?" << endl;
                    cin >> answer;
                    Card* chainOrDiscard = gameTable->tArea.trade(*iter);
                    while(chainOrDiscard != nullptr) {
                        // If yes add all cards of bean type T to chain
                        if(answer == "yes" || answer == "Yes") addToChain(gameTable->p1, *gameTable, -1, chainOrDiscard);
                        else gameTable->dPile += chainOrDiscard; // If no discard all cards in trade area of type T
                        chainOrDiscard = gameTable->tArea.trade(*iter);
                    }
                }
            }
            cout << endl;

            // Play topmost card
            cout << "Top card : ";
            gameTable->p1.printHand(cout ,false);
            cout << endl;
            cardToChain = gameTable->p1.hand.play();

            addToChain(gameTable->p1, *gameTable, index, cardToChain);

            cout << "Top card : ";
            gameTable->p1.printHand(cout, false);
            cout << endl;

            cout << "Game : Do you wish to add your top card to a chain?" << endl;
            cout << gameTable->p1.getName() << " : "; cin >> answer;

            if(answer == "yes" || answer == "Yes")
            {
                cardToChain = gameTable->p1.hand.play();
                addToChain(gameTable->p1, *gameTable, index, cardToChain);
            }

            cout << "Game : Would you like to discard a card from your hand?" << endl;
            cout << gameTable->p1.getName() << " : "; cin >> answer;

            if(answer == "yes" || answer == "Yes")
            {
                gameTable->p1.printHand(cout, true); cout << endl;

                cout << "Game : What card would you like to discard?" << endl;

                for(;;)
                {
                    cout << gameTable->p1.getName() << " : "; cin >> answer;
                    Card* discardCard = gameTable->p1.hand[position];


                    if(discardCard != nullptr)
                    {
                        gameTable->dPile += discardCard;
                        cout << gameTable->p1.getName() << " hand : "; gameTable->p1.printHand(cout, true); cout << endl;
                        break;
                    }
                }
            }
            // Place 3 cards into the trade area.
            for(int i = 0; i < 3 && !gameTable->deck.empty(); ++i)
            {
                gameTable->tArea += (gameTable->deck.draw());
            }

            //for all the cards in the trade area, compare top card
            while(gameTable->dPile.top() != nullptr && gameTable->tArea.legal(gameTable->dPile.top()))
            {
                gameTable->tArea += (gameTable->dPile.pickUp());
            }

            cout << endl;
            cout << "Trade Area : "; cout << gameTable->tArea << endl;

            // While the trade area is not empty, ask a user if they want to add each card to your chain, if not, leave it for the next player.
            if(gameTable->tArea.numCards() != 0)
            {
                for(auto iter = gameTable->tArea.cardTypes.begin(); iter != gameTable->tArea.cardTypes.end();)
                {
                    cout << "Game : Do you want to add " << *iter << " to a chain?" << endl;
                    cout << gameTable->p1.getName() << " : "; cin >> answer;

                    if(answer == "yes" || answer == "Yes")
                    {
                        Card* chainOrDiscard = gameTable->tArea.trade(*iter);

                        while(chainOrDiscard != nullptr)
                        {
                            addToChain(gameTable->p1, *gameTable, -1, chainOrDiscard);
                            chainOrDiscard = gameTable->tArea.trade(*iter);
                        }

                        iter = gameTable->tArea.cardTypes.erase(iter);
                    } else {
                         ++iter;
                    }
                }
            }
            if( !gameTable->deck.empty() ) {
                gameTable->p1.hand += gameTable->deck.draw();
                gameTable->p1.hand += gameTable->deck.draw();
            }
            playerTurn = 2;
        }

        cout << "Game : Here is the gameTable as it stands :" << endl;
        cout << endl;
        cout << "############## GAME gameTable ##############" << endl;
        cout << *gameTable;
        cout << "########################################" << endl;
        cout << endl;


        // Keep track of turn.
        if(playerTurn == 2)
        {
            // Chain purchasing.
            if(gameTable->p2.getMaxNumChains() < 3)
            {
                string answer = "";
                cout << "Game : Would you like to buy your third chain " << gameTable->p2.getName() << "?" << endl;
                cout << "[Buy third chain? yes or no]" << endl;
                cout << gameTable->p2.getName() << " : ";
                cin >> answer;

                if(answer == "yes")
                {
                    gameTable->p2.buyThirdChain();
                }
            }

            // Player draws a card.
            if(!gameTable->deck.empty())
            {
                cout << "Game : Draw a card before continuing!" << endl;
                Card* drawCard = gameTable->deck.draw();
                cout << "[You draw " + drawCard->getName() + "]" << endl;
                gameTable->p2.hand.operator+=(drawCard);

                gameTable->p2.printHand(cout, true);
            }

            if(gameTable->tArea.numCards() != 0)
            {
                for(auto iter = gameTable->tArea.cardTypes.begin(); iter != gameTable->tArea.cardTypes.end(); iter = gameTable->tArea.cardTypes.erase(iter))
                {
                    cout << endl;
                    cout << "Game : Do you want to add " << *iter << " to a chain?" << endl;
                    cout << gameTable->p2.getName() << " : "; cin >> answer;

                    Card* chainOrDiscard = gameTable->tArea.trade(*iter);

                    while(chainOrDiscard != nullptr)
                    {
                        if(answer == "yes" || answer == "Yes")
                        {
                            addToChain(gameTable->p2, *gameTable, -1, chainOrDiscard);
                        }else{
                            gameTable->dPile += chainOrDiscard;
                        }

                        chainOrDiscard = gameTable->tArea.trade(*iter);
                    }
                }
            }
            cout << endl;

            // Play topmost card
            cout << "Top card : ";
            gameTable->p2.printHand(cout ,false);
            cout << endl;
            cardToChain = gameTable->p2.hand.play();

            addToChain(gameTable->p2, *gameTable, index, cardToChain);

            cout << "Top card : ";
            gameTable->p2.printHand(cout, false);
            cout << endl;

            cout << "Game : Do you wish to add your top card to a chain?" << endl;
            cout << gameTable->p2.getName() << " : "; cin >> answer;

            if(answer == "yes" || answer == "Yes")
            {
                cardToChain = gameTable->p2.hand.play();
                addToChain(gameTable->p2, *gameTable, index, cardToChain);
            }

            cout << "Game : Would you like to discard a card from your hand?" << endl;
            cout << gameTable->p2.getName() << " : "; cin >> answer;

            if(answer == "yes" || answer == "Yes")
            {
                gameTable->p2.printHand(cout, true); cout << endl;

                cout << "Game : What card would you like to discard?" << endl;

                for(;;)
                {
                    cout << gameTable->p2.getName() << " : "; cin >> answer;
                    Card* discardCard = gameTable->p2.hand[position];


                    if(discardCard != nullptr)
                    {
                        gameTable->dPile += discardCard;
                        cout << gameTable->p2.getName() << " hand : "; gameTable->p2.printHand(cout, true); cout << endl;
                        break;
                    }
                }
            }
            // Place 3 cards into the trade area.
            for(int i = 0; i < 3 && !gameTable->deck.empty(); ++i)
            {
                gameTable->tArea += (gameTable->deck.draw());
            }

            // For all the cards in the trade area, compare top card
            while(gameTable->dPile.top() != nullptr && gameTable->tArea.legal(gameTable->dPile.top()))
            {
                gameTable->tArea += (gameTable->dPile.pickUp());
            }

            cout << endl;
            cout << "Trade Area : "; cout << gameTable->tArea << endl;
            
            // While the trade area is not empty, ask a user if they want to add each card to your chain, if not, leave it for the next player.
            if(gameTable->tArea.numCards() != 0)
            {
                for(auto iter = gameTable->tArea.cardTypes.begin(); iter != gameTable->tArea.cardTypes.end();)
                {
                    cout << "Game : Do you want to add " << *iter << " to a chain?" << endl;
                    cout << gameTable->p2.getName() << " : "; cin >> answer;

                    if(answer == "yes" || answer == "Yes")
                    {
                        Card* chainOrDiscard = gameTable->tArea.trade(*iter);

                        while(chainOrDiscard != nullptr)
                        {
                            addToChain(gameTable->p2, *gameTable, -1, chainOrDiscard);
                            chainOrDiscard = gameTable->tArea.trade(*iter);
                        }

                        iter = gameTable->tArea.cardTypes.erase(iter);
                    } else {
                         ++iter;
                    }
                }
            }
            if( !gameTable->deck.empty() ) {
                gameTable->p2.hand += gameTable->deck.draw();
                gameTable->p2.hand += gameTable->deck.draw();
            }
            playerTurn = 1;
        }
    }

	if (winner == "Tie") cout << "Congratulations to the both of you!" << endl;
	else cout << "Congratulations " << winner << ". You've won!" << endl;

	delete gameTable;
	// delete players[0];
	// delete players[1];

	return 0;
}
