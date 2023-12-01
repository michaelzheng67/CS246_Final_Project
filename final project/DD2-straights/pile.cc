#include "pile.h"
#include "card.h"
#include <vector>
#include <algorithm>


Pile::Pile(std::vector<int> cards, char suit, int lowestlegal, int highestlegal): cards{cards}, suit{suit}, lowestlegal{lowestlegal}, highestlegal{highestlegal} {}


void Pile::addCard(Card* card) {
    if (card->getValue() == highestlegal) {
        highestlegal++;
    } 
    
    if (card->getValue() == lowestlegal) {
        lowestlegal--;
    }

    cards.push_back(card->getValue());
    // sort pile after every add
    std::sort(cards.begin(), cards.end());
}

void Pile::removeCard() {
    cards.pop_back();
}

std::vector<int> Pile::getCards() {
    return cards;
}

char Pile::getSuit() {
    return suit;
}

std::vector<int> Pile::legalPlays() {
    std::vector<int> temp;
    temp.push_back(lowestlegal);
    temp.push_back(highestlegal);
    return temp;
}

int Pile::getLowest() {
    return lowestlegal;
}

int Pile::getHighest() {
    return highestlegal;
}

void Pile::setLowest(int lowest) {
    lowestlegal = lowest;
}

void Pile::setHighest(int highest) {
    highestlegal = highest;
}
