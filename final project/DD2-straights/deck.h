#ifndef _DECK_H_
#define _DECK_H_

#include "card.h"
#include <vector>
#include <random>


class Deck {
    std::vector<Card *>cards;
    unsigned index;
    public:
        Deck(std::vector<Card *> cards);
        Deck(Deck* other_deck);
	
	std::vector<Card *> getCards();
	void shuffle( std::default_random_engine seed );
	Card* dealCard();


};

#endif
