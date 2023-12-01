#ifndef _TEXTOBSERVER_H_
#define _TEXTOBSERVER_H_
#include "observer.h"
#include "board.h"
#include "player.h"
#include "deck.h"

#include <vector>

class Textobserver : public Observer {
    Board *subject;
    Deck* playing_deck;
    public:
        Textobserver( Board *subject );
	void notify() override;
	~Textobserver();

};

#endif
