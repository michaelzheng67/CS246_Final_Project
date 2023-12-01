#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

#include "player.h"
#include "computer.h"
#include "human.h"
#include "card.h"
#include "deck.h"
#include "board.h"
#include "textobserver.h"

using std::cin;
using std::cout;
using std::endl;
using std::cerr;

// main harness
//


int main( int argc, char * argv[] ) {


    // 
    //
    //
    // Setting up everything before the game iterations begin 
    //
    //
    //

    
    // create board (subject) and necessary observers
    
    // when board is created, so is its corresponding piles and deck	
    Board board{};
    Textobserver observer{ &board };




    // calls observers to display intro and create four players
    board.notifyObservers();
    board.setIntro(false);

    // if end of file
    if (cin.eof()) {
        return 0;
    }




    // optional: get command line argument for seeding
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    
    if ( argc > 1 ) {
        try {
	    seed = std::stoi(argv[1]);
	} catch( std::invalid_argument & e ) {
	    cerr << e.what() << endl;
	    return 1;
	} catch ( std::out_of_range & e ) {
	    cerr << e.what() << endl;
	}
    }

    // seeding based on argument number given
    std::default_random_engine rng{seed};





    // shuffle 
    board.getPlayingDeck()->shuffle(rng);




    // 
    //
    // Running of the actual game iterations
    //
    //
    //


    // game loop ends once a winner is determined
    while(true) {

	// give players cards
	board.setIndex(0);
        while (true) {
            for (int i=0; i < 13; i++) {
                board.addPlayerCards(board.getPlayingDeck()->dealCard());
	    }
	    board.incrementIndex();

	    if (board.getIndex() == 0) {
	        break;
	    }

        }

        int starting_player = board.findstart();
        board.setIndex( starting_player );


	// announce the new round
	//
	//
	board.setNewround(true);

	// keep playing the current round while players still have cards 
	while( board.cardsRemaining() ) {

	    // display player move
	    board.notifyObservers();
	   

	    // if end of file 
	    if (cin.eof()) {
	        return 0;
	    }


	    // if player commanded to quit the game
	    if (board.getQuit()) {
		return 0;
		break;


	     // if player commanded to ragequit the game
	     } else if (board.getRagequit()) {
		board.replacePlayer();
		board.setRagequit(false);
		board.Textplay();	
	     }


	    // increment player index after player turn is done
	    board.incrementIndex();
	}

	// once game is done, show the scores and reset everything to start state
	board.notifyObservers();
	board.reset();



	// see if board produced a winner
	if (board.findWinner() != -1) {
	    break;
	}


	// shuffle deck after round to start new round
	board.getPlayingDeck()->shuffle(rng);
    }
}






