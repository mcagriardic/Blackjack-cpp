#pragma once

class BlackJack : public Deck {
private:
	bool m_allStand;
public:
	int playerCount;
	int noOfDecks;
	vector<Participants*> participants;

	BlackJack (int playerCount=1, int noOfDecks=1)
		: playerCount(playerCount), Deck(noOfDecks)
	{
		setPlayers();
		dealCards();
	};

	~BlackJack() {
		for (Participants* obj : participants)
			delete obj;
		participants.clear();
	}

	vector<Participants*> getParticipants() const {
		return participants;
	};

	void printDeck() {
		print();
	}

	void printCards(bool isGame=false) {
		for (int i = 0; i < participants.size(); i++) {
			participants[i]->printCards(isGame);
		}
	}

	bool checkIfInitialWinner() 
	{
		for (int i = 0; i < participants.size(); i++) {
			if (participants[i]->getisWinner())
			{
				printCards(false);
				if (i == 0)
				{
					cout << "Dealer wins the game!" << endl << endl;
				}
				else 
				{
					cout << "Player " << i << " wins!" << endl << endl;
				}
				return true;
			}
		}
		return false;
	}


	void setallStand() {
		m_allStand = true;
		for (int i = 0; i < participants.size(); i++) {
			if (!participants[i]->getStand()) 
			{
				m_allStand = false;
			}
		}
	}

	bool play() {

		string directive;

		bool winner;
		int round = 1;

		if (checkIfInitialWinner())
		{
			return NULL;
		}

		while (!m_allStand) {

			for (size_t i = 0; i < participants.size(); i++) {
				{

					if (i == 0 && round != 1) {
						cout << "Dealer's turn!" << endl;
						if (participants[i]->getScore() <= 15) {
							cout << "Dealer hits..." << endl << endl;
							winner = hit(participants[i]);
							participants[i]->setStand(false);

							if (winner) {
								printCards(false);
								return NULL;
							}

							else if (!participants[i]->getcanPlay()) {
								cout << "Player wins the game! Dealer goes bust!" << endl << endl;
								printCards(false);
								return NULL;
							}
						}
						else {
							cout << "Dealer stands..." << endl << endl;
							participants[i]->setStand(true);
						}
					}

					else if ( i != 0 && participants[i]->getcanPlay())
					{
						cout << "Player " << i << "'s turn..." << endl;
						cout << "Player " << i << ", do you wish to hit or stand?" << endl;
						cin >> directive;

						if (directive.compare("hit") == 0) {
							cout << "Player " << i << " hits..." << endl << endl;
							winner = hit(participants[i]);
							participants[i]->setStand(false);
							if (winner) {
								printCards(false);
								return NULL;
							}
							else if (!participants[i]->getcanPlay()) {
								participants[i]->setStand(true);
								printCards(false);

								if (playerCount == 1)
								{
									return NULL;
								}
							}
						} 

						else if (directive.compare("stand") == 0) {
							cout << "Player " << i << " stands..." << endl << endl;
							participants[i]->setStand(true);
						}
						cout << endl;
					}
					round++;
					setallStand();
					printCards(true);

					if (m_allStand) {

						int highestScore = 0;
						int winnerIdx;

						for (int i = 0; i < participants.size(); i++) {
							if (participants[i]->getcanPlay());
							{
								if (participants[i]->getScore() > highestScore) {
									highestScore = participants[i]->getScore();
									winnerIdx = i;
								}
							}
						}
						if (winnerIdx == 0) {
							cout << "Dealer wins!" << endl << endl;
						}
						else {
							cout << "Player " << i << " wins!" << endl << endl;
						}
						printCards(false);
						return NULL;
					}
				}
			}
		}
	}

private:
	int m_noOfCards = 2;

	void setPlayers() {
		Dealer* d = new Dealer();
		Participants* dealer = d;
		participants.push_back(dealer);

		for (int i = 0; i < playerCount; i++)
		{
			Player* p = new Player(i + 1);
			Participants* player = p;
			participants.push_back(player);
		}
	};

	Card popCard() {
		Card poppedCard = deck.back();
		deck.pop_back();
		return poppedCard;
	}

	void dealCards() {
		for (size_t i = 0; i < participants.size(); i++) {
			for (int j = 0; j < m_noOfCards; j++)
			{
				participants[i]->addCard(&popCard());
			}
		}
	}
	
	bool hit(Participants* participant) {
		return participant->addCard(&popCard());
	}

	void stand(Participants* participant)
	{
		if (participant->getPlayerIdx() == 0)
		{
			cout << "Dealer stands..." << endl;
		}
		else {
			cout << "Player " << participant->getPlayerIdx() << " stands..." << endl;
		}
	}
};




// this causes code duplication but allows memory access
// which one is the better solution here:
// the implementation above or below

//void dealCards() {
//	for (size_t i = 0; i < participants.size(); i++) {
//		for (int j = 0; j < m_noOfCards; j++)
//		{
//			Card* poppedCard = &deck.back();
//			participants[i]->addCard(poppedCard);
//			deck.pop_back();
//		}
//	}
//}
//
//void hit(Participants* participant) {
//	Card* poppedCard = &deck.back();
//	participant->addCard(poppedCard);
//	deck.pop_back();
//}