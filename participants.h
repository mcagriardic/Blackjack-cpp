#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H

#include "deck.h"

class Participants {
public:
	virtual void addCard(Card* cards) = 0;
	virtual void printCards(const bool&) const = 0;
	virtual int getParticipantIdx() const = 0;
	virtual bool getcanPlay() const = 0;
	virtual int getScore() const = 0;
	virtual void collectPrevRoundCards() = 0;
};

#endif
