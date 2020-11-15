#ifndef HAND_H
#define HAND_H

#include "card.h"

class Hand {
public:
	int score = 0;
	vector<Card> cards;
	bool hasAce = false;
	bool isHandBust = false;
	bool isHandWinner = false;
	int  idxBelongsToPlayer;
    int  handIdx;

	Hand(int&, int&);

	int  getScore() const;
	int  getIdxBelongsToPlayer() const;
	bool getisHandWinner() const;
	bool getisHandBust() const;
	int  gethandIdx() const;

	void sethasAce(const bool&);
	void setisHandBust(const bool&);
	void setisHandWinner(const bool&);

	void displayHand(const bool&) const;
	void addCard(Card*);
	void recalculateScore();
	void clearHand();
	void adjustForAce(Card*);

};

#endif