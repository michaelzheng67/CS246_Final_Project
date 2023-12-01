#ifndef _BOARD_H_
#define _BOARD_H_


#include <string>
#include <vector>
#include <memory>
#include "pile.h"
#include "card.h"
#include "subject.h"
#include "player.h"
#include "deck.h"

class Board : public Subject {
    std::vector<std::unique_ptr<Player> >players;
    std::vector<Pile *>piles;
    Deck* playing_deck;
    std::vector<Card*>playing_cards;

    int current_index;

    bool intro = true;
    bool newround = true;
    bool quit = false;
    bool ragequit = false;
    public:
        Board();

	// sets starting index for player rotation
	void setIndex( int index );

	// changes index to next player
	void incrementIndex();

	// get the index
	int getIndex();



	// returns boolean indicating whether any player's still have cards
	bool cardsRemaining();



	// returns whether given card would be a legal play
	bool legalPlay(int value, char suit);

	// plays one of the players' turn
	void Textplay();

	// plays one of the players' turn with given card
	void Textplay(Card * card);

	// discards the players' given card
	void discard(Card * card);

	

	// returns int that corresponds to position in vector of players that starts first (finds player with 7S)
	// returns -1 if no 7S is found
	int findstart();

	// get pile cards on board (for testing)
	void getPiles();

	// returns the vector holding the piles
	std::vector<Pile *> getPileVector();
	

	// returns index where winner is in vector of players. If no winner yet, returns -1 
	int findWinner();

	// replaces current player with given player. Specifically useful for "ragequit" command
	void replacePlayer();

	// scores the round and outputs text
	void scoreRound();	

	// empties all cards in players discard and from piles
	void reset();

	
	// add different type of players to players array
	void addHuman(int counter);
	void addComputer(int counter);


	// remove last player from players
	void removePlayer();

	void addPile(Pile *pile);
	void removePile();

	void setIntro(bool command);
	bool getIntro();

	void setQuit(bool command);
	bool getQuit();

	void setRagequit(bool command);
	bool getRagequit();

	void setNewround(bool command);
	bool getNewround();

	
	Deck* getPlayingDeck();
	int getPlayerNum();
	
	//get certain states
	std::string getType();

	void addPlayerCards(Card* card);
 	std::vector<Card *> getPlayerCards();
		

	//Player* getCurrentPlayer();
	std::vector<int> getStateSpades();
	std::vector<int> getStateDiamonds();
	std::vector<int> getStateClubs();
	std::vector<int> getStateHearts();

	// destructor
	~Board();


};

#endif




