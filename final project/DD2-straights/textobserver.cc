#include "textobserver.h"
#include <iostream>
#include "player.h"
#include "deck.h"
#include "outputhelpers.h"

#include <vector>

using std::cout;
using std::cin;
using std::endl;
using Outputhelpers::InttoSymbol;

Textobserver::Textobserver( Board *subject ) : subject{subject} {
    subject->attach( this );
}

Textobserver::~Textobserver() {
    subject->detach( this );
}


void Textobserver::notify() {


    // prints if its an introduction
    if (subject->getIntro()) {
        // create the four players
        int num_players = 4;
        int counter = 1;


        while (counter < num_players + 1) {
            char type = ' ';
            cout << "Is Player" << counter << " a human (h) or a computer (c) ?" << endl;

            cin >> type;

	    if (cin.eof()) {
	        cout << "End of file detected. Game shutting down now." << endl;
		return;
		break;
	    }

            if (type == 'h') {
                subject->addHuman(counter);
                counter++;
            }

            else if (type == 'c') {
                subject->addComputer(counter);
                counter++;
            }


            else {
                cout << "Invalid input. Try again." << endl;

            }
        }

	// ensures that this is the only text being displayed
	return;
    }



    // print if its a new round
    if (subject->getNewround()) {
        subject->setNewround(false);
	cout << "A new round begins. It's Player" << subject->getIndex()+1 << "'s turn to play." << endl;

    }


    if (subject->cardsRemaining()) {
	// if human, get input for comman
        if (subject->getType() == "Human" ) {
	    subject->Textplay();

	    std::string command;
	    while (cin >> command) {

		// play command 
	        if (command == "play") {
		    int value;
		    char char_value;
		    char suit;

		    // either number or face card
		    if (cin >> value) {
		        cin >> suit;
		    } else {
		        cin.clear();
			cin >> char_value;
			cin >> suit;

			// convert face value to respective number value
			if (char_value == 'J') {
			    value = 11;
			} else if (char_value == 'Q') {
			    value = 12;
			} else if (char_value == 'K') {
			    value = 13;
			} else if (char_value == 'A') {
			    value = 1;
			}
		    }

		    // boolean to check if card was played
		    bool played = false;

		    // find corresponding card in hand and play it, given that its a legal play
		    for (auto & card : subject->getPlayerCards()) {
		        if (card->getValue() == value && card->getSuit() == suit && subject->legalPlay(card->getValue(), card->getSuit())) {
			    subject->Textplay(card);
			    played = true;
			    cout << "player" << subject->getPlayerNum() << " plays " << InttoSymbol(value) << suit << "." << endl;
			    break;
			}
		    }

		    if (played) {
		        break;
		    }
	            cout << "This is not a legal play." << endl;




		// discard command
		} else if (command == "discard") {
		    int value;
		    char char_value;
		    char suit;

		    if (cin >> value) {
		        cin >> suit;
		    } else {
		        cin.clear();
			cin >> char_value;
			cin >> suit;

			if (char_value == 'J') {
			    value = 11;
			} else if (char_value == 'Q') {
			    value = 12;
			} else if (char_value == 'K') {
			    value = 13;
			} else if (char_value == 'A') {
			    value = 1;
			}
		    }

		    // if legal play, not allowed
		    bool legalplay = false;
		    for (auto & card : subject->getPlayerCards()) {
		        if (subject->legalPlay(card->getValue(), card->getSuit())) {
			    cout << "You have a legal play. You may not discard." << endl;
			    legalplay = true;
			    break;
			}
		    }

		    // if no legal play exists, discard chosen card
		    bool discarded = false;
		    if (!legalplay) {
		        for (auto & card : subject->getPlayerCards()) {
			    if (card->getValue() == value && card->getSuit() == suit) {
			        subject->discard(card);
				cout << "player" << subject->getPlayerNum() << " discards " << InttoSymbol(card->getValue()) << card->getSuit() << "." << endl;
				discarded = true;
				break;
			    }
			}
			if (discarded) {
			    break;
			}
			cout << "not a card in your hand." << endl;
		    }



		// deck command    
		} else if (command == "deck") {
		    int counter = 0;
		    for (auto & card : subject->getPlayingDeck()->getCards()) {
		        cout << InttoSymbol(card->getValue()) << card->getSuit() << " ";
			counter++;

			if (counter == 13) {
			    counter = 0;
			    cout << endl;
			}
		    }  



		} else if (command == "quit") {

		    subject->setQuit(true);
		    

		    break;
		

		} else if (command == "ragequit") {
		    cout << "Player" << subject->getIndex() + 1 << " ragequits. A computer will now take over." << endl;
		    subject->setRagequit(true);

		    break;



		} else {
		    cout << "invalid command. Please try again." << endl;
		}
	  }

	  if (cin.eof()) {
              cout << "End of file detected. Game shutting down now." << endl;
              return;
          }

	// any other player (computer)
	} else {
	    subject->Textplay();
	}
	    

    // if no more cards to play, score the round
    } else {
        subject->scoreRound();


	// if someone has a gamescore >= 80 and there is a winner
        if (subject->findWinner() != -1) {
            cout << "Player" << subject->findWinner() + 1 << " wins!" << endl;
        }

    }
}
