#include "board.h"

#include <vector>
#include <vector>
#include "pile.h"
#include "player.h"
#include "computer.h"
#include "human.h"
#include <iostream>

Board::Board(){
    std::vector<Card*> playing_cards;
    // clubs
    for (int i=1; i < 14; i++) {
        Card *temp_card = new Card(i, 'C');
        playing_cards.push_back(temp_card);
    }

    // diamonds
    for (int i=1; i < 14; i++) {
        Card *temp_card = new Card(i, 'D');
        playing_cards.push_back(temp_card);
    }

    // hearts
    for (int i=1; i < 14; i++) {
        Card *temp_card = new Card(i, 'H');
        playing_cards.push_back(temp_card);
    }

    // spades
    for (int i=1; i < 14; i++) {
        Card *temp_card = new Card(i, 'S');
        playing_cards.push_back(temp_card);
    }

    // store playing cards to delete later
    this->playing_cards = playing_cards;

    // playing deck
    playing_deck = new Deck(playing_cards);



    // make piles
    Pile *spades = new Pile(std::vector<int>(), 'S', 7, 7);
    Pile *diamonds = new Pile(std::vector<int>(), 'D', 7, 7);
    Pile *clubs = new Pile(std::vector<int>(), 'C', 7, 7);
    Pile *hearts = new Pile(std::vector<int>(), 'H', 7, 7);

    this->addPile(spades);
    this->addPile(diamonds);
    this->addPile(clubs);
    this->addPile(hearts);

}


void Board::setIndex( int index ) {
    current_index = index;
    newround = true;
}


void Board::incrementIndex() {
    if (current_index == 3) {
        current_index = 0;
    } else {
        current_index++;
    }

}

int Board::getIndex() {
    return current_index;
}

bool Board::cardsRemaining() {
    int numEmpty = 0;
    for (auto & player : players) {
        if (player->getHand().empty()) {
	    numEmpty++;
	}
    }
    
    if (numEmpty == 4) {
        return false;
    }
    return true;
}

bool Board::legalPlay(int value, char suit) {
    for (auto & legalcard : players[current_index]->getLegalInHand(piles)) {
        if (legalcard->getValue() == value && legalcard->getSuit() == suit) {
	    return true;
	}
    }

    return false;
    
}

void Board::Textplay() {
    // get player and give it piles for it to run
    players[current_index]->Textplay(piles);
    
}

void Board::Textplay(Card * card) {
    // remove card from players hand
    players[current_index]->removeCard(card);

    // add card to correct pile
    if (card->getSuit() == 'S') {
        piles[0]->addCard(card);

    } else if (card->getSuit() == 'D') {
        piles[1]->addCard(card);

    } else if (card->getSuit() == 'C') {
        piles[2]->addCard(card);

    } else if (card->getSuit() == 'H') {
        piles[3]->addCard(card);

    }

}

void Board::discard(Card * card) {
    // removed card from players hand;
    players[current_index]->removeCard(card);
    // add card to discard pile
    players[current_index]->addDiscard(card);
}

int Board::findstart() {
    int return_position = -1;
    // iterate through all players
    for (auto & player : players) {
	return_position++;
        // iterate through all cards in hand
	for (auto & card : player->getHand()) {
	   if (card->getValue() == 7 && card->getSuit() == 'S') {
	       return return_position;
	   } 
	}
    }
    return -1;
}

void Board::getPiles() {
    for (auto & pile : piles) {
        std::cout << pile->getSuit();
	for (auto & card : pile->getCards()) {
	    std::cout << " " << card;
	}
	std::cout << std::endl;
    }
}

std::vector<Pile*> Board::getPileVector() {
    return piles;
}



int Board::findWinner() {
    bool gameEnded = false;
    for (auto & player : players ) {
        if (player->getGamescore() >= 80) {
	    gameEnded = true;
	    break;
	}
    }

    int index = 0;
    if (gameEnded) {
        int smallestScore = players[0]->getGamescore();
        for (int i=0; i < 4; i++) {
            if (players[i]->getGamescore() < smallestScore) {
	        smallestScore = players[i]->getGamescore();
	        index = i;
	    }
        }
    }

    if (gameEnded) {
        return index;
    } else {
	return -1;
    }



}


void Board::replacePlayer() {
    // get current player and delete its memory
    players[current_index].reset(new Computer{*players.at(current_index).get()});
}



// helper function for outputting cards
std::string InttoSymbol(int value) {
    std::string temp;
    if (value <= 10 && value >= 2) {
        temp = std::to_string(value);
    } else if (value == 11) {
        temp = "J";
    } else if (value == 12) {
        temp = "Q";
    } else if (value == 13) {
        temp = "K";
    } else if (value == 1) {
        temp = "A";
    }
    return temp;

}



void Board::scoreRound() {
    for (auto & player : players) {
	// iterate through discard and output along with add to score
	std::cout << "Player" << player->getPlayerNum() << "'s discards: "; 
        for (auto & card : player->getDiscard()) {
	    std::cout << InttoSymbol(card->getValue()) << card->getSuit() << " ";
	    player->addRoundscore(card->getValue());
	}
	std::cout << std::endl;

	// output players score equation
	std::cout << "Player" << player->getPlayerNum() << "'s score: ";
	std::cout << player->getGamescore() << " + " << player->getRoundscore() << " = ";
	
	// new gamescore
	player->addGamescore(player->getRoundscore());
        std::cout << player->getGamescore() << std::endl;

	// reset roundscore
	player->resetRoundscore();
    }
}

void Board::reset() {
    // remove all cards from player discard piles
    for (auto & player : players) {
        while (!player->getDiscard().empty()) {
	    player->removeDiscard();
	}
    }

    // remove all cards from pile
    for ( auto & pile : piles) {
        while (!pile->getCards().empty()) {
	    pile->removeCard();
	}
	pile->setLowest(7);
	pile->setHighest(7);	
    }



}

void Board::addHuman(int counter) {
    players.push_back(std::move(std::make_unique<Human>(0,0,counter,std::vector<Card*>(), std::vector<Card*>())));
}

void Board::addComputer(int counter) {
    players.push_back(std::move(std::make_unique<Computer>(0,0,counter,std::vector<Card*>(), std::vector<Card*>())));
}

void Board::removePlayer() {
    players.pop_back();
}


void Board::addPile(Pile* pile) {
    piles.push_back(pile);
}

void Board::removePile() {
    piles.pop_back();
}

void Board::setIntro(bool command) {
    intro = command;
}

bool Board::getIntro() {
    return intro;
}

void Board::setQuit(bool command) {
    quit = command;
}

bool Board::getQuit() {
    return quit;
}

void Board::setRagequit(bool command) {
    ragequit = command;
}

bool Board::getRagequit() {
    return ragequit;
}

void Board::setNewround(bool command) {
    newround = command;
}

bool Board::getNewround() {
    return newround;
}

Deck* Board::getPlayingDeck() {
    return playing_deck;
}

int Board::getPlayerNum() {
    return players[current_index]->getPlayerNum();
}

std::string Board::getType() {
    return players[current_index]->getPlayerType();
}

void Board::addPlayerCards(Card* card) {
    players[current_index]->addCard(card);
}

std::vector<Card *> Board::getPlayerCards() {
    return players[current_index]->getHand();
}

std::vector<int> Board::getStateSpades() {
    return piles[0]->legalPlays();
}

std::vector<int> Board::getStateDiamonds() {
    return piles[1]->legalPlays(); 
}

std::vector<int> Board::getStateClubs() {
    return piles[2]->legalPlays();
}

std::vector<int> Board::getStateHearts() {
    return piles[3]->legalPlays();
}


Board::~Board() {

    for (auto & pile : piles) {
        delete pile;
    }

    for (auto & card : playing_cards) {
        delete card;
    }

    delete playing_deck;

}






