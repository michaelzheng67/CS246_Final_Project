#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "card.h"
#include "observer.h"
#include "pile.h"

#include <vector>
#include <string>

class Player {
    int gamescore;
    int roundscore;
    int player_num;
    std::vector<Card>cards;
    std::vector<Card>discard;

    public:
        //Player( int gamescore, int roundscore, int player_num, std::vector<Card> cards, std::vector<Card>discard);
        virtual void addCard(Card* card) = 0;
	virtual void removeCard(Card* card) = 0;
	virtual void removeCard() = 0;
	virtual std::vector<Card*> getHand() = 0;

	virtual void addDiscard(Card* card) = 0;
	virtual void removeDiscard() = 0;
	virtual std::vector<Card*> getDiscard() = 0;

	virtual void addGamescore(int score) = 0;
	virtual void addRoundscore(int round) = 0;
	virtual int getGamescore() = 0;
        virtual int getRoundscore() = 0;
	virtual void resetRoundscore() = 0;

	virtual int getPlayerNum() = 0;

	virtual void Textplay(std::vector<Pile *>piles) = 0;
	virtual std::string getPlayerType() = 0;
	virtual ~Player();

	virtual std::vector<Card*> getLegalInHand(std::vector<Pile*> piles) = 0;
};

#endif
