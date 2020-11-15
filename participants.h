#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H

#include "deck.h"
#include "hand.h"

class Participants {
public:
	virtual void             displayHand(Hand *hand, const bool& isStateDealing) const = 0;

	virtual bool             isDealer() = 0;
	
	virtual bool             getcanPlay() const = 0;
	virtual bool             getisWinner() const = 0;
	virtual int              getParticipantIdx() const = 0;
	virtual vector<Hand*>    getHands() const = 0;
	virtual int              getnoOfHands() const = 0;
	virtual Hand*            getHandByIdx(const int&) const = 0;
	virtual Hand*            getLastHand() const = 0;
	virtual bool             gethasRefusedSplit() const = 0;

	virtual void             setcanPlay(const bool&) = 0;
	virtual void             setisWinner(const bool&) = 0;
	virtual void             sethasRefusedSplit(const bool&) = 0;
	virtual void             setisHandBust(const int&, const bool&) = 0;

	virtual void             recalculateScore(Hand* hand) = 0;
	virtual void             createHand() = 0;
	virtual void             addCard(Hand*, Card*) = 0;
	virtual void             collectPrevRoundCards() = 0;
};

#endif
