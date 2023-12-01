#include "card.h"
#include "deck.h"
#include <vector>
#include <algorithm>
#include <random>

Deck::Deck(std::vector<Card *> cards): cards{cards}, index{0} {}

Deck::Deck(Deck* other_deck): cards{other_deck->getCards()}, index{0} {}

std::vector<Card *> Deck::getCards() {
    return cards;
}

void Deck::shuffle( std::default_random_engine seed ) {
    std::shuffle( cards.begin(), cards.end(), seed);
}

Card* Deck::dealCard() {
    Card *temp = cards[index];

    // reset index if at end of deck
    if (index == cards.size() - 1) {
        index = 0;
    } else {
        index++;
    }
    return temp;
}

