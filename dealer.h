#ifndef DEALER_H
#define DEALER_H

#include "participants.h"

class Dealer : public Participants {
private:
	bool m_hasAce = false;
public:
	int uniqueID = 0;
	bool canPlay = true;
	bool isWinner = false;
	int noOfHands = 1;
	int handIdx = 0;
	vector<Hand*> hands;

	Dealer();
	void             displayHand(Hand*, const bool& = false) const override;

	bool             isDealer() override;

	bool             getisWinner() const override;
	bool             getcanPlay() const override;
	int              getParticipantIdx() const override;
	vector<Hand*>    getHands() const override;
	int              getnoOfHands() const override;
	Hand*            getHandByIdx(const int&) const override;
	Hand*            getLastHand() const override;
	bool             gethasRefusedSplit() const override;


	void             setcanPlay(const bool&) override;
	void             setisWinner(const bool&) override;
	void             sethasRefusedSplit(const bool&) override;
	void             setisHandBust(const int&, const bool&) override;

	void             recalculateScore(Hand*) override;
	void             createHand() override;
	void             addCard(Hand*, Card*) override;
	void             collectPrevRoundCards() override;
};

#endif