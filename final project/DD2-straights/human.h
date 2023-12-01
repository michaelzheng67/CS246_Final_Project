#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "card.h"
#include <vector>
#include <string>
#include "player.h"
class Human: public Player {
    int gamescore;
    int roundscore;
    int player_num;
    std::vector<Card*>cards;
    std::vector<Card*>discard;

    public:
        Human(int gamescore, int roundscore, int player_num, std::vector<Card*>cards, std::vector<Card*>discard);
        virtual void addCard(Card* card) override;
	virtual void removeCard(Card* card) override;
	virtual void removeCard() override;
	virtual std::vector<Card*> getHand() override;
	
	virtual void addDiscard(Card* card) override;
	virtual void removeDiscard() override;
	virtual std::vector<Card*> getDiscard() override;

	virtual void addGamescore(int score) override;
	virtual void addRoundscore(int round) override;
	virtual int getGamescore() override;
	virtual int getRoundscore() override;
	virtual void resetRoundscore() override;

	virtual int getPlayerNum() override;

	virtual void Textplay(std::vector<Pile *> piles) override; 
	virtual std::string getPlayerType() override;

	virtual std::vector<Card*> getLegalInHand(std::vector<Pile*> piles) override;
	~Human();


};

#endif
