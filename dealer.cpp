#include <iostream>
#include "dealer.h"

int Dealer::getParticipantIdx() const {
	return participantIdx;
}

bool Dealer::getcanPlay() const {
	return canPlay;
}

int Dealer::getScore() const {
	return score;
}

void Dealer::collectPrevRoundCards() {
	cards.clear();
	score = 0;
}

void Dealer::printCards(bool isStateDealing) const {
	cout << "Dealer's cards are... " << endl;
	for (size_t i = 0; i < cards.size(); i++)
	{
		if (i == 0 && isStateDealing) {
			cout << "*** HIDDEN ***" << endl;
			continue;
		}
		cards[i].print();
	}
	cout << endl;
}

/* === HIT DIRECTIVES === */

void Dealer::addCard(Card* card) {
	cards.push_back(*card);
	score += card->val;

	adjustForAce(card);
}

void Dealer::adjustForAce(Card* card) {
	if (card->rank.compare("Ace") == 0 || m_hasAce) {
		m_hasAce = true;
		if (score > 21) {
			score -= 10;
			m_hasAce = false;
		}
	}
}