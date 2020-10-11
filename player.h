#pragma once

class Player : public Participants {
private:
	vector<Card> m_cards;
	bool m_hasAce = false;
public:
	int playerIdx;
	bool canPlay = true;
	bool isWinner = false;
	bool stands = false;
	int score = 0;


	Player(int playerIdx=1)
		: playerIdx(playerIdx)
	{ ; }

	int getPlayerIdx() const override {
		return playerIdx;
	}

	bool getcanPlay() const override {
		return canPlay;
	}
	 
	bool getisWinner() const override {
		return isWinner;
	}

	int getScore() const override
	{
		return score;
	}

	bool getStand() const override {
		return stands;
	}

	void setStand(bool stand) {
		stands = stand;
	}

	void printInfo() const override {
		cout << "This is a player and the idx is " << playerIdx << endl;
	}

	void printCards(bool isGame = false) const override {
		if (canPlay) 
		{
			cout << "Player " << playerIdx << "'s cards are... " << endl;
		}
		for (size_t i = 0; i < m_cards.size(); i++)
		{
			if (canPlay)
			{
				m_cards[i].print();
			}
			
		}
		if (canPlay)
		{
			cout << "Total score: " << score << endl << endl;
		}
		
	}

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
			cout << "Player " << playerIdx << " wins the game!" << endl;
			isWinner = true;
		}
		else if (score > 21) {
			cout << "Player " << playerIdx << " is out of the game!" << endl << endl;
			printCards(false);
			canPlay = false;
		}
		//return { isWinner, canPlay };
	}

};