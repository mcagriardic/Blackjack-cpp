#pragma once

class Dealer : public Participants {
private:
	vector<Card> m_cards;
	bool m_hasAce = false;
public:
	const int playerIdx = 0;
	bool canPlay = true;
	bool isWinner = false;
	bool stands = false;
	int score = 0;

	string name;

	Dealer(string name = "Bob")
		: name(name)
	{
		;
	}

	int getPlayerIdx() const override {
		return playerIdx;
	}

	bool getcanPlay() const override {
		return canPlay;
	}

	bool getisWinner() const override {
		return isWinner;
	}

	int getScore() const override {
		return score;
	}

	bool getStand() const override {
		return stands;
	}

	void setStand(bool stand) override {
		stands = stand;
	}

	void printInfo() const override {
		cout << "This is a dealer and his name is " << name << endl;
	}

	void printCards(bool isGame = false) const override {
		cout << "Dealer's cards are... " << endl;
		for (size_t i = 0; i < m_cards.size(); i++)
		{
			if (i == 0 && isGame) {
				cout << "*** HIDDEN ***" << endl;
				continue;
			}
			m_cards[i].print();
		}
		cout << endl;
	}

	/* === HIT DIRECTIVES === */

	bool addCard(Card* card) override {
		m_cards.push_back(*card);
		score += card->val;

		adjustForAce(card);
		checkScore();

		return isWinner;
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

	void checkScore() {

		if (score == 21) {
			cout << "Dealer wins the game!" << endl << endl;
			isWinner = true;
		}
		else if (score > 21) {
			cout << "Dealer is out of the game! Player's win the game!" << endl << endl;
			canPlay = false;
		}
	}

	/* ================ */
};