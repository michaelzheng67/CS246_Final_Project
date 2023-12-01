#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include <vector>
#include <string>
#include "card.h"
#include "player.h"

class Computer: public Player {
    int gamescore;
    int roundscore;
    int player_num;
    std::vector<Card*>cards;
    std::vector<Card*>discard;

    public:
        Computer(int gamescore, int roundscore, int player_num, std::vector<Card*>cards, std::vector<Card*>discard);
        Computer(Player &other_player);
	
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

        virtual void Textplay(std::vector<Pile *>piles) override;
	virtual std::string getPlayerType() override;

	std::string InttoSymbol(int value);
	virtual std::vector<Card*> getLegalInHand(std::vector<Pile*> piles) override;	
	~Computer();	
};

#endif
