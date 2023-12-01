#ifndef _PILE_H_
#define _PILE_H_

#include <vector>
#include "card.h"


class Pile {
    std::vector<int>cards;
    char suit;
    int lowestlegal;
    int highestlegal;
    public:
        Pile(std::vector<int> cards, char suit, int lowestlegal, int highestlegal);
        void addCard(Card* card);
	void removeCard();
	std::vector<int> getCards();
	char getSuit();
	std::vector<int> legalPlays();

	int getLowest();
	int getHighest();
	void setLowest(int lowest);
	void setHighest(int highest);
};

#endif
