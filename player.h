#pragma once

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

	Player()
	{ 
		participantIdx = uniqueID++;
	}

	int getParticipantIdx() const override {
		return participantIdx;
	}

	bool getcanPlay() const override {
		return canPlay;
	}
	 
	int getScore() const override
	{
		return score;
	}

	void collectPrevRoundCards() override {
		cards.clear();
		score = 0;
	}

	void printCards(bool isStateDealing) const override {
		if (canPlay) 
		{
			cout << "Player " << participantIdx << "'s cards are... " << endl;
		}
		for (size_t i = 0; i < cards.size(); i++)
		{
			if (canPlay)
			{
				cards[i].print();
			}
			
		}
		if (canPlay)
		{
			cout << "Total score: " << score << endl << endl;
		}
	}

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

int Player::uniqueID = 1;