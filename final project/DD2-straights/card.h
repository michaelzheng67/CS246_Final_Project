#ifndef _CARD_H_
#define _CARD_H_

class Card {
    int value;
    char suit;
    public:
        Card(int value, char suit);
        int getValue();
	char getSuit();


};

#endif
