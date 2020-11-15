#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "participants.h"

class Player : public Participants {
protected:
	static int uniqueID;
private:
public:
	int participantIdx;
	bool canPlay = true;
	bool isWinner = false;
	bool hasRefusedSplit = false;
	int noOfHands = 0;
	int handIdx = 0;
	vector<Hand*> hands;

	Player();
	void             displayHand(Hand*, const bool& = false) const override;

	bool             isDealer() override;
	
	bool             getcanPlay() const override;
	bool             getisWinner() const override;
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
	//void sethasAce(const bool&) override;

	void             recalculateScore(Hand*) override;
	void             createHand() override;
	void             addCard(Hand*, Card*) override;
	void             collectPrevRoundCards() override;
};

#endif