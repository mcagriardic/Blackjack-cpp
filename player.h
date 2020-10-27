#pragma once

#include "participants.h"
#ifndef PLAYER_H
#define PLAYER_H

class Player : public Participants {
protected:
	static int uniqueID;
private:
	bool m_hasAce = false;
public:
	int participantIdx;
	bool canPlay = true;
	int score = 0;
	vector<Card> cards;

	Player();
	int  getParticipantIdx() const override;
	bool isDealer() override;
	bool getcanPlay() const override;
	int  getScore() const override;
	void collectPrevRoundCards() override;
	void printCards(const bool& isStateDealing = false) const override;
	void addCard(Card* card) override;
	void adjustForAce(Card* card);
};

#endif