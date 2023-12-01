#include "computer.h"
#include "card.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
using std::cout;
using std::endl;


Computer::Computer(int gamescore, int roundscore, int player_num, std::vector<Card*>cards, std::vector<Card*>discard): gamescore{gamescore}, roundscore{roundscore}, player_num{player_num}, cards{cards}, discard{discard} {}

Computer::Computer(Player& other_player): gamescore{other_player.getGamescore()}, roundscore{other_player.getRoundscore()}, player_num{other_player.getPlayerNum()}, cards{other_player.getHand()}, discard{other_player.getDiscard()} {}

void Computer::addCard(Card* card) {
    cards.push_back(card);
}

void Computer::removeCard(Card* card) {
    cards.erase(std::remove(cards.begin(), cards.end(), card), cards.end());
}

void Computer::removeCard() {
    cards.pop_back();
}

std::vector<Card*> Computer::getHand() {
    return cards;
}

void Computer::addDiscard(Card* card) {
    discard.push_back(card);
}

void Computer::removeDiscard() {
    discard.pop_back();
}

std::vector<Card*> Computer::getDiscard() {
    return discard;
}

void Computer::addGamescore(int score) {
    gamescore += score;
}

void Computer::addRoundscore(int round) {
    roundscore += round;
}

int Computer::getGamescore() {
    return gamescore;
}

int Computer::getRoundscore() {
    return roundscore;
}

void Computer::resetRoundscore() {
    roundscore = 0;
}

int Computer::getPlayerNum() {
    return player_num;
}



// helper function for outputting cards
std::string Computer::InttoSymbol(int value) {
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

void Computer::Textplay(std::vector<Pile *> piles) {
    for (auto &card : cards) {
        for (auto &pile : piles) {
	    // same suit
	    if (card->getSuit() == pile->getSuit()) {
	        for (auto value : pile->legalPlays()) {
		    if (card->getValue() == value) {
			cout << "Player" << player_num << " plays " << InttoSymbol(card->getValue()) << card->getSuit() << "." << endl;		        
		        pile->addCard(card);
			cards.erase(std::remove(cards.begin(), cards.end(), card), cards.end());
			return;
		    }
		}
	    } 
	} 
    }
   
   // no matches, discard first card in hand
   cout << "Player" << player_num << " discards " << InttoSymbol(cards[0]->getValue()) << cards[0]->getSuit() << "." << endl;
   addDiscard(cards[0]);
   cards.erase(cards.begin() + 0); 
}

std::string Computer::getPlayerType() {
    return "Computer";
}

std::vector<Card*> Computer::getLegalInHand(std::vector<Pile*> piles) {
    std::vector<Card*> temp;

    for (auto & card : cards) {
        for (auto & pile : piles) {
	    if (card->getSuit() == pile->getSuit()) {
	        for (auto value : pile->legalPlays()) {
		    if (card->getValue() == value) {
		        temp.push_back(card);
		    }
		}
	    }
	}
    }
    
    return temp;
}

Computer::~Computer() {}
