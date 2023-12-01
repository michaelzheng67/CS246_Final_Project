#include "card.h"

Card::Card(int value, char suit): value{value}, suit{suit} {}


int Card::getValue() {
    return value;
}

char Card::getSuit() {
    return suit;
}

