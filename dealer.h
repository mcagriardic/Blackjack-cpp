#ifndef DEALER_H
#define DEALER_H

#include "participants.h"

class Dealer : public Participants {
private:
	bool m_hasAce = false;
public:
	const int participantIdx = 0;
	bool canPlay = true;
	bool isWinner = true;
	int score = 0;
	vector<Card> cards;

	int  getParticipantIdx() const override;
	bool isDealer() override;
	void setcanPlay(const bool& status) override;
	bool getcanPlay() const override;
	bool getisWinner() const override;
	void setisWinner(const bool&) override;
	int  getScore() const override;
	void collectPrevRoundCards() override;
	void printCards(const bool& isStateDealing = false) const override;
	void addCard(Card* card) override;
	void adjustForAce(Card* card);
};

#endif