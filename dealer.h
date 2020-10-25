#pragma once

class Dealer : public Participants {
private:
	bool m_hasAce = false;
public:
	const int participantIdx = 0;
	bool canPlay = true;
	int score = 0;
	vector<Card> cards;

	int getParticipantIdx() const override {
		return participantIdx;
	}

	bool getcanPlay() const override {
		return canPlay;
	}

	int getScore() const override {
		return score;
	}

	void collectPrevRoundCards() override {
		cards.clear();
		score = 0;
	}

	void printCards(bool isStateDealing=false) const override {
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

	void addCard(Card* card) override {
		cards.push_back(*card);
		score += card->val;

		adjustForAce(card);
	}

	void adjustForAce(Card* card) {
		if (card->rank.compare("Ace") == 0 || m_hasAce) {
			m_hasAce = true;
			if (score > 21) {
				score -= 10;
				m_hasAce = false;
			}
		}
	}
};