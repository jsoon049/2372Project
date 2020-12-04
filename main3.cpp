// //Backup in case i randomly mess up main.cpp
// #include <stdio.h>
// #include <iostream>
// #include <fstream>
// #include <string.h>

// #include "hand.cpp"
// #include "tradeArea.cpp"
// #include "table.cpp"
// #include <exception>

// struct IllegalTyp : public exception {
//     const char * err () const throw () { 
//         return "Type Error: Card type does not match chain type!"; 
//     }
// };

// void addToChain(Player& _player, Table& table, int chainNumber, Card* topCard)
// {
//         cout << "Game : Please choose a chain to add " << topCard->getName() << " to." << endl;
        
//         while(chainNumber < 0 || chainNumber >= _player.getMaxNumChains())
//         {
//             cout << _player.getName() << " : " ; cin >> chainNumber;
//         }

//         ChainBase* chosenChain = &_player[chainNumber];

//         if(chosenChain->isEmpty())
//         {
//             _player.addChain(chainNumber, topCard);
//         }else{
//             try{
//                 *chosenChain += (topCard);
//             }
//             catch(IllegalTyp &e)
//             {
//                 string answer;
//                 cout << "Game : Card types do not match, would you like to sell this chain?" << endl;
//                 cout << _player.getName() << " : "; cin >> answer;

//                 if(answer == "yes" || answer == "Yes")
//                 {
//                     _player += (chosenChain->sell());
//                     _player.addChain(chainNumber, topCard);
//                 }else{
//                     addToChain(_player, table, -1, topCard);
//                 }
//             }
//     }
// }

// void saveGame(Table& _table)
// {
//     string answer;
//     cout << "Would you like to save the game to file?" << endl;
//     cin >> answer;

//     if( answer == "yes" || answer == "Yes")
//     {
//         string fn{"gemstones_save.txt"};
//         // open file
//         ofstream out(fn);
//         if( !out || fn == "README.txt" || fn == "README") {
//             cout << "ERROR: unable to open " << fn << endl << endl;
//             saveGame( _table );
//             return;
//         }

//         // print table contents to file
//         _table.printAll(out);

//         // close file
//         out.close();
//     }
// }

// Table* loadGame (CardFactory* _cardPool) {
//     string fn;
//     cout << "Enter file name : "; cin >> fn;
//     // open file
//     ifstream in(fn);
//     if( !in ) {
//         cout << "ERROR: unable to open " << fn << endl << endl;
//         return loadGame( _cardPool );
//     }

//     // read contents from file
//     return new Table( in, _cardPool );
// }

// int main(void)
// {
//     // Variable creation/initialization at startup.
//     Player playerOne;										// Player one
//     string playerOneName;									// Player one name
//     Player playerTwo;										// Player two
//     string playerTwoName;									// Player two name
// 	Player* players[2];
//     CardFactory cardFactory = *CardFactory::getFactory();   // Create the instance of cardfactory
//     string gameType;										// 0 = new new, 1 = new, 2 = loadup
//     int turn = 1;											// 1 = p1, 2 = p2
//     int chainNumber = -1;									// 1 = chain 1, 2 = chain 2
//     Table* table;
//     Card* topCard;
//     string answer;
//     int choice;
//     string winner = "";

//     // Load from save file or nah?
//     while(gameType != "1" || gameType != "2") {
//         cout << "Game : Would you like to start a new game [1], or load from save file [2]?" << endl;
//         cout << "You : ";
//         cin >> gameType;     
//         if(gameType == "1")
//         {
//             gameType = "1";
//             break;
//         }else if(gameType == "2")
//         {
//             gameType = "2";
//             break;
//         }else{
//             gameType = "0";
//         }
//     }

//     //======================== CREATE A NEW GAME ========================
//     if(gameType == "1")
//     {
// 		table = new Table();
//         // Player one name input.
//         cout << "Game : What is your name Player 1?" << endl;
//         cout << "Player One : ";
//         cin >> playerOneName;

//         // If player one is trying to be smart.
//         if(playerOneName == "")
//         {
//             cout << "Game : I guess I shall assign you a name .. 'Player One'" << endl;
//             playerOneName = "Player One";
//         }

//         // Player one is made.
// 		players[0] = new Player(playerOneName);
// 		table->p1= *players[0];

//         // Player two name input.
//         cout << "Game : What is your name Player 2?" << endl;
//         cout << "Player Two : ";
//         cin >> playerTwoName;

//         // If player two is trying to be smart.
//         if(playerTwoName == "")
//         {
//             cout << "Game : I guess I shall assign you a name .. 'Player Two'" << endl;
//             playerTwoName = "Player Two";
//         }

//         // Player two is made.
// 		players[1] = new Player(playerTwoName);
// 		table->p2 = *players[1];

// 		// Deck, taken from factory
// 		table->deck = cardFactory.getDeck();

//         // Give both players 5 cards to start.
//         for(int i = 0; i < 5; ++i)
//         {
//             table->p1.hand+=(table->deck.draw());
//             table->p2.hand+=(table->deck.draw());
//         }
//     }else{
// 		// load from file
//         table = loadGame( cardFactory.getFactory() );
//     }


//     // Game time.
//     while(!table->win(winner))
//     {
//         cout << "Game : Here is the table as it stands :" << endl;
//         cout << endl;
//         cout << "############## GAME TABLE ##############" << endl;
//         cout << *table;
//         cout << "########################################" << endl;
//         cout << endl;

//         saveGame( *table );

//         // Keep track of turn.
//         if(turn == 1)
//         {
//             // Chain purchasing.
//             if(table->p1.getMaxNumChains() < 3)
//             {
//                 string answer = "";
//                 cout << "Game : Would you like to buy your third chain " << table->p1.getName() << "?" << endl;
//                 cout << "[Buy third chain? yes or no]" << endl;
//                 cout << table->p1.getName() << " : ";
//                 cin >> answer;

//                 if(answer == "yes")
//                 {
//                     table->p1.buyThirdChain();
//                 }
//             }

//             // Player draws a card.
//             if(!table->deck.empty())
//             {
//                 cout << "Game : Draw a card before continuing!" << endl;
//                 Card* drawCard = table->deck.draw();
//                 cout << "[You draw " + drawCard->getName() + "]" << endl;
//                 table->p1.hand.operator+=(drawCard);

//                 table->p1.printHand(cout, true);
//             }
            
//             // This version of checking if the trade area ends up deleting the trade area cards until it's 0.
//             if(table->tArea.numCards() != 0)
//             {
//                 for(auto iter = table->tArea.cardTypes.begin(); iter != table->tArea.cardTypes.end(); iter = table->tArea.cardTypes.erase(iter))
//                 {
//                     cout << endl;
//                     cout << "Game : Do you want to add " << *iter << " to a chain?" << endl;
//                     cout << table->p1.getName() << " : "; cin >> answer;

//                     Card* cardInTrade = table->tArea.trade(*iter);

//                     while(cardInTrade != nullptr)
//                     {
//                         if(answer == "yes" || answer == "Yes")
//                         {
//                             addToChain(table->p1, *table, -1, cardInTrade);
//                         }else{
//                             table->dPile += cardInTrade;
//                         }

//                         cardInTrade = table->tArea.trade(*iter);
//                     }
//                 }
//             }
//             cout << endl;

//             // Play topmost card
//             cout << "Top card : ";
//             table->p1.printHand(cout ,false);
//             cout << endl;
//             topCard = table->p1.hand.play();

//             addToChain(table->p1, *table, chainNumber, topCard);

//             cout << "Top card : ";
//             table->p1.printHand(cout, false);
//             cout << endl;

//             cout << "Game : Do you wish to add your top card to a chain?" << endl;
//             cout << table->p1.getName() << " : "; cin >> answer;

//             if(answer == "yes" || answer == "Yes")
//             {
//                 topCard = table->p1.hand.play();
//                 addToChain(table->p1, *table, chainNumber, topCard);
//             }

//             cout << "Game : Would you like to discard a card from your hand?" << endl;
//             cout << table->p1.getName() << " : "; cin >> answer;

//             if(answer == "yes" || answer == "Yes")
//             {
//                 table->p1.printHand(cout, true); cout << endl;

//                 cout << "Game : What card would you like to discard?" << endl;

//                 for(;;)
//                 {
//                     cout << table->p1.getName() << " : "; cin >> choice;
//                     Card* discardCard = table->p1.hand[choice];


//                     if(discardCard != nullptr)
//                     {
//                         table->dPile += discardCard;
//                         cout << table->p1.getName() << " hand : "; table->p1.printHand(cout, true); cout << endl;
//                         break;
//                     }
//                 }
//             }
//             // Place 3 cards into the trade area.
//             for(int i = 0; i < 3 && !table->deck.empty(); ++i)
//             {
//                 table->tArea += (table->deck.draw());
//             }

//             //for all the cards in the trade area, compare top card
//             while(table->dPile.top() != nullptr && table->tArea.legal(table->dPile.top()))
//             {
//                 table->tArea += (table->dPile.pickUp());
//             }

//             cout << endl;
//             cout << "Trade Area : "; cout << table->tArea << endl;

//             // While the trade area is not empty, ask a user if they want to add each card to your chain, if not, leave it for the next player.
//             if(table->tArea.numCards() != 0)
//             {
//                 for(auto iter = table->tArea.cardTypes.begin(); iter != table->tArea.cardTypes.end();)
//                 {
//                     cout << "Game : Do you want to add " << *iter << " to a chain?" << endl;
//                     cout << table->p1.getName() << " : "; cin >> answer;

//                     if(answer == "yes" || answer == "Yes")
//                     {
//                         Card* cardInTrade = table->tArea.trade(*iter);

//                         while(cardInTrade != nullptr)
//                         {
//                             addToChain(table->p1, *table, -1, cardInTrade);
//                             cardInTrade = table->tArea.trade(*iter);
//                         }

//                         iter = table->tArea.cardTypes.erase(iter);
//                     } else {
//                          ++iter;
//                     }
//                 }
//             }
//             if( !table->deck.empty() ) {
//                 table->p1.hand += table->deck.draw();
//                 table->p1.hand += table->deck.draw();
//             }
//             turn = 2;
//         }

//         cout << "Game : Here is the table as it stands :" << endl;
//         cout << endl;
//         cout << "############## GAME TABLE ##############" << endl;
//         cout << *table;
//         cout << "########################################" << endl;
//         cout << endl;


//         // Keep track of turn.
//         if(turn == 2)
//         {
//             // Chain purchasing.
//             if(table->p2.getMaxNumChains() < 3)
//             {
//                 string answer = "";
//                 cout << "Game : Would you like to buy your third chain " << table->p2.getName() << "?" << endl;
//                 cout << "[Buy third chain? yes or no]" << endl;
//                 cout << table->p2.getName() << " : ";
//                 cin >> answer;

//                 if(answer == "yes")
//                 {
//                     table->p2.buyThirdChain();
//                 }
//             }

//             // Player draws a card.
//             if(!table->deck.empty())
//             {
//                 cout << "Game : Draw a card before continuing!" << endl;
//                 Card* drawCard = table->deck.draw();
//                 cout << "[You draw " + drawCard->getName() + "]" << endl;
//                 table->p2.hand.operator+=(drawCard);

//                 table->p2.printHand(cout, true);
//             }

//             if(table->tArea.numCards() != 0)
//             {
//                 for(auto iter = table->tArea.cardTypes.begin(); iter != table->tArea.cardTypes.end(); iter = table->tArea.cardTypes.erase(iter))
//                 {
//                     cout << endl;
//                     cout << "Game : Do you want to add " << *iter << " to a chain?" << endl;
//                     cout << table->p2.getName() << " : "; cin >> answer;

//                     Card* cardInTrade = table->tArea.trade(*iter);

//                     while(cardInTrade != nullptr)
//                     {
//                         if(answer == "yes" || answer == "Yes")
//                         {
//                             addToChain(table->p2, *table, -1, cardInTrade);
//                         }else{
//                             table->dPile += cardInTrade;
//                         }

//                         cardInTrade = table->tArea.trade(*iter);
//                     }
//                 }
//             }
//             cout << endl;

//             // Play topmost card
//             cout << "Top card : ";
//             table->p2.printHand(cout ,false);
//             cout << endl;
//             topCard = table->p2.hand.play();

//             addToChain(table->p2, *table, chainNumber, topCard);

//             cout << "Top card : ";
//             table->p2.printHand(cout, false);
//             cout << endl;

//             cout << "Game : Do you wish to add your top card to a chain?" << endl;
//             cout << table->p2.getName() << " : "; cin >> answer;

//             if(answer == "yes" || answer == "Yes")
//             {
//                 topCard = table->p2.hand.play();
//                 addToChain(table->p2, *table, chainNumber, topCard);
//             }

//             cout << "Game : Would you like to discard a card from your hand?" << endl;
//             cout << table->p2.getName() << " : "; cin >> answer;

//             if(answer == "yes" || answer == "Yes")
//             {
//                 table->p2.printHand(cout, true); cout << endl;

//                 cout << "Game : What card would you like to discard?" << endl;

//                 for(;;)
//                 {
//                     cout << table->p2.getName() << " : "; cin >> choice;
//                     Card* discardCard = table->p2.hand[choice];


//                     if(discardCard != nullptr)
//                     {
//                         table->dPile += discardCard;
//                         cout << table->p2.getName() << " hand : "; table->p2.printHand(cout, true); cout << endl;
//                         break;
//                     }
//                 }
//             }
//             // Place 3 cards into the trade area.
//             for(int i = 0; i < 3 && !table->deck.empty(); ++i)
//             {
//                 table->tArea += (table->deck.draw());
//             }

//             // For all the cards in the trade area, compare top card
//             while(table->dPile.top() != nullptr && table->tArea.legal(table->dPile.top()))
//             {
//                 table->tArea += (table->dPile.pickUp());
//             }

//             cout << endl;
//             cout << "Trade Area : "; cout << table->tArea << endl;
            
//             // While the trade area is not empty, ask a user if they want to add each card to your chain, if not, leave it for the next player.
//             if(table->tArea.numCards() != 0)
//             {
//                 for(auto iter = table->tArea.cardTypes.begin(); iter != table->tArea.cardTypes.end();)
//                 {
//                     cout << "Game : Do you want to add " << *iter << " to a chain?" << endl;
//                     cout << table->p2.getName() << " : "; cin >> answer;

//                     if(answer == "yes" || answer == "Yes")
//                     {
//                         Card* cardInTrade = table->tArea.trade(*iter);

//                         while(cardInTrade != nullptr)
//                         {
//                             addToChain(table->p2, *table, -1, cardInTrade);
//                             cardInTrade = table->tArea.trade(*iter);
//                         }

//                         iter = table->tArea.cardTypes.erase(iter);
//                     } else {
//                          ++iter;
//                     }
//                 }
//             }
//             if( !table->deck.empty() ) {
//                 table->p2.hand += table->deck.draw();
//                 table->p2.hand += table->deck.draw();
//             }
//             turn = 1;
//         }
//     }

// 	if (winner == "Tie") cout << "Congratulations to the both of you!" << endl;
// 	else cout << "Congratulations " << winner << ". You've won!" << endl;

// 	delete table;
// 	delete players[0];
// 	delete players[1];

// 	return 0;
// }
