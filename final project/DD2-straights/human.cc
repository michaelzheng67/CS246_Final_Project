#include "human.h"

#include "outputhelpers.h"
#include "card.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;
using std::cin;
using Outputhelpers::InttoSymbol;

Human::Human(int gamescore, int roundscore, int player_num, std::vector<Card*>cards, std::vector<Card*>discard): gamescore{gamescore}, roundscore{roundscore}, player_num{player_num}, cards{cards}, discard{discard} {}

void Human::addCard(Card* card) {
    cards.push_back(card);
}

void Human::removeCard(Card* card) {
    cards.erase(std::remove(cards.begin(), cards.end(), card), cards.end());
}

void Human::removeCard() {
    cards.pop_back();
}

std::vector<Card*> Human::getHand() {
    return cards;
}

void Human::addDiscard(Card* card) {
    discard.push_back(card);
}

void Human::removeDiscard() {
    discard.pop_back();
}

std::vector<Card*> Human::getDiscard() {
    return discard;
}

void Human::addGamescore(int score) {
    gamescore += score;
}

void Human::addRoundscore(int round) {
    roundscore += round;
}

int Human::getGamescore() {
    return gamescore;
}

int Human::getRoundscore() {
    return roundscore;
}

void Human::resetRoundscore() {
    roundscore = 0;
}

int Human::getPlayerNum() {
    return player_num;
}



void Human::Textplay(std::vector<Pile * > piles) {
    cout << "Cards on the table:" << endl;
    
    int clubs;
    int diamonds;
    int hearts;
    int spades;
    for (int i=0; i < 4; i++) {
        if (piles[i]->getSuit() == 'C') {
	    clubs = i;
	} else if (piles[i]->getSuit() == 'D') {
	    diamonds = i;
	} else if (piles[i]->getSuit() == 'H') {
	    hearts = i;
	} else if (piles[i]->getSuit() == 'S') {
	    spades = i;
	}
    }

    cout << "Clubs:";
    for (auto & card : piles[clubs]->getCards()) {
        cout << " " << card;
    }
    cout << endl;

    cout << "Diamonds: ";
    for (auto & card : piles[diamonds]->getCards()) {
        cout << " " << card;
    }
    cout << endl;
    
    cout << "Hearts: ";
    for (auto & card : piles[hearts]->getCards()) {
        cout << " " << card;
    }
    cout << endl;

    cout << "Spades: ";
    for (auto & card : piles[spades]->getCards()) {
        cout << " " << card;
    }
    cout << endl;

    cout << "Your hand:";
   
    // loop through hand and print out cards
    for (auto &card : cards) {
        cout << " " << InttoSymbol(card->getValue()) << card->getSuit();
    }   
    cout << endl;

    cout << "Legal plays:";

    // loop through hand and piles for legal plays
    for (auto &card : cards) {
        for (auto &pile : piles) {
	    if (pile->getSuit() == card->getSuit()) {
	        if (pile->getLowest() == card->getValue() || pile->getHighest() == card->getValue()) {
		    cout << " " << InttoSymbol(card->getValue()) << card->getSuit();
	        }
	    }
	}
    }
    cout << endl;


}



std::string Human::getPlayerType() {
    return "Human";
}


std::vector<Card*> Human::getLegalInHand(std::vector<Pile*> piles) {
    std::vector<Card*> temp;

    for (auto & card : cards) {
        for (auto & pile : piles) {
	    if (pile->getSuit() == card->getSuit()) {
		if (pile->getLowest() == card->getValue() || pile->getHighest() == card->getValue()) {
		    temp.push_back(card);
		}
	    }
	}
    }

    return temp;
    
}


Human::~Human() {}








