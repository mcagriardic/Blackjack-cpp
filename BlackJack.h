#pragma once

class BlackJack{
private:
	bool m_allStand;
public:
	int playerCount;
	int noOfDecks;
	Deck deck;
	FSM fsm;
	size_t* turnIdx;
	string activeState = "dealing";
	vector<Participants*> participants;

	BlackJack (int _playerCount=1, int _noOfDeck=1)
		: playerCount(_playerCount), noOfDecks(_noOfDeck)
	{
		setFSM();
		setPlayers();
	};

	BlackJack() = default;

	~BlackJack() {
		for (Participants* obj : participants)
			delete obj;
		participants.clear();
		delete game;
	}

	void printDeck() {
		deck.print();
	}

	void printCards(bool isStateDealing=false) {
		for (int i = 0; i < participants.size(); i++) {
			participants[i]->printCards(isStateDealing);
		}
	}

	void play() {

		string directive;

		// while there are transitions to make, run the while loop
		// only the "quit" state has no transitions
		while (!fsm.states[activeState].transitions.empty()) {

			for (size_t turnIdx_temp = 0; turnIdx_temp < participants.size(); turnIdx_temp++)
			{
				turnIdx = &turnIdx_temp;

				if (activeState.compare("dealing") == 0) {
					deck.createDeck(noOfDecks);
					dealCards();
					activeState = fsm.evaluate(activeState, "dealt");
					printCards(true);
				}

				if (activeState.compare("playerTurn") == 0 && *turnIdx != 0)
				{
					cout << "Player " << *turnIdx << "'s turn..." << endl;
					cout << "Player " << *turnIdx << ", do you wish to hit or stand?" << endl;

					if (participants[*turnIdx]->getScore() < 17)
					{
						cout << "Player hits!" << endl << endl;
						hit(participants[*turnIdx]);
						activeState = fsm.evaluate(activeState, "hit");
					}
					else
					{
						cout << "Player stands!" << endl << endl;
						activeState = fsm.evaluate(activeState, "stand");
					}
					printCards();
				}

				else if (activeState.compare("dealerTurn") == 0) {
					cout << "Dealer's turn!" << endl;

					if (participants[*turnIdx]->getScore() < 17)
					{
						cout << "Dealer hits!" << endl << endl;
						hit(participants[*turnIdx]);
						activeState = fsm.evaluate(activeState, "hit");
					}
					else
					{
						cout << "Dealer stands!" << endl << endl;
						activeState = fsm.evaluate(activeState, "stand");
					}
					printCards();
				}

				if (activeState.compare("loss") == 0)
				{
					cout << "Participant " << *turnIdx << " is out of the game..." << endl;
					
					if (participants.size() == 2) {
						if (*turnIdx == 0) {
							cout << "Player has won the game!" << endl;
						}
						else {
							cout << "Dealer has won the game!" << endl;
						}
					}
					activeState = fsm.evaluate(activeState, "replay");
				}

				else if (activeState.compare("standOff") == 0) {
					cout << "Draw..." << endl;
					activeState = fsm.evaluate(activeState, "replay");
				}

				else if (activeState.compare("win") == 0) {
					cout << "Participant " << *turnIdx << " wins the game!..." << endl;
					activeState = fsm.evaluate(activeState, "replay");
				}

				if (activeState.compare("restart") == 0) {
					cout << "Do you wish to play again?..." << endl;
					/*cin >> directive;*/
					directive = "yes";
					activeState = fsm.evaluate(activeState, directive);

					collectPrevRoundCards();
					deck.clearDeck();
				}
			}
		}
	}

private:
	int m_noOfCards = 2;

	void setFSM() {
		fsm.setCurState("dealing");

		fsm.addState("dealing", setDealingState());
		fsm.addState("playerTurn", setplayerTurnState());
		fsm.addState("dealerTurn", setdealerTurnState());
		fsm.addState("loss", setlossState());
		fsm.addState("standOff", setstandOffState());
		fsm.addState("win", setwinState());
		fsm.addState("restart", setRestartState());
		fsm.addState("quit", setquitState());
	}

	void setPlayers() {
		Dealer* d = new Dealer();
		Participants* dealer = d;
		participants.push_back(dealer);

		for (int i = 0; i < playerCount; i++)
		{
			Player* p = new Player();
			Participants* player = p;
			participants.push_back(player);
		}
	};

	Card popCard() {
		Card poppedCard = deck.activeDeck.back();
		deck.activeDeck.pop_back();
		return poppedCard;
	}

	void collectPrevRoundCards() {
		for (size_t i = 0; i < participants.size(); i++) {
			participants[i]->collectPrevRoundCards();
		}
	}

	void dealCards() {
		for (size_t i = 0; i < participants.size(); i++) {
			for (int j = 0; j < m_noOfCards; j++)
			{
				participants[i]->addCard(&popCard());
			}
		}
	}
	
	void hit(Participants* participant) {
		participant->addCard(&popCard());
	}

	void stand(Participants* participant)
	{
		if (participant->getParticipantIdx() == 0)
		{
			cout << "Dealer stands..." << endl;
		}
		else {
			cout << "Player " << participant->getParticipantIdx() << " stands..." << endl;
		}
	}
};





//cin >> directive;
//
//if (directive.compare("hit") == 0)
//{
//	cout << "Player " << *turnIdx << " hits..." << endl << endl;
//	hit(participants[*turnIdx]);
//	activeState = fsm.evaluate(activeState, directive);
//}
//
//else if (directive.compare("stand") == 0) {
//	cout << "Player " << *turnIdx << " stands..." << endl << endl;
//	activeState = fsm.evaluate(activeState, directive);
//}