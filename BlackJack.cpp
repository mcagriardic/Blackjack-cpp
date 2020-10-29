#include "BlackJack.h"

extern BlackJack* blackjack;

BlackJack::BlackJack(const int& _playerCount, const  int& _noOfDeck)
	: playerCount(_playerCount), noOfDecks(_noOfDeck)
{
	setFSM();
	setPlayers();
};

BlackJack::~BlackJack() {
	for (Participants* obj : participants)
		delete obj;
	participants.clear();

	delete blackjack;
}

void BlackJack::printDeck() {
	deck.print();
}

void BlackJack::printCards(const bool& isStateDealing) {
	for (int i = 0; i < participants.size(); i++) {
		participants[i]->printCards(isStateDealing);
	}
}

int BlackJack::getCurrentPlayerScore()
{
	return participants[turnIdx]->getScore();
}

void BlackJack::play() {
	
	fsm.evaluate("none");

	// while there are transitions to make, run the while loop
	// only the "quit" state has no transitions
	while (!fsm.states[fsm.activeState].transitions.empty()) {
		for (size_t turnIdx_temp = 0; turnIdx_temp < participants.size(); turnIdx_temp++)
		{
			turnIdx = turnIdx_temp;
			fsm.evaluate(event);
		}
	}
}

/* =========================== STATE CALLBACKS =========================== */

void BlackJack::onEnterState_dealing() {
	deck.createDeck(noOfDecks);
	dealCards();
	printCards(true);
	event = "dealt";
}

void BlackJack::onEnterState_playerTurn() {
	cout << "Player " << turnIdx << "'s turn..." << endl;
	cout << "Player " << turnIdx << ", do you wish to hit or stand?" << endl;

	if (participants[turnIdx]->getScore() < 17)
	{
		cout << "Player hits!" << endl << endl;
		hit(participants[turnIdx]);
		printCards();
		event = "hit";
	}
	else
	{
		cout << "Player stands!" << endl << endl;
		event = "stand";
	}
}

void BlackJack::onEnterState_dealerTurn() {
	cout << "Dealer's turn!" << endl;

	if (participants[turnIdx]->getScore() < 17)
	{
		cout << "Dealer hits!" << endl << endl;
		hit(participants[turnIdx]);
		printCards();
		event = "hit";
	}
	else
	{
		cout << "Dealer stands!" << endl << endl;
		event = "stand";
	}
}

void BlackJack::onEnterState_loss() 
{
	cout << "Participant " << turnIdx << " wins the game!..." << endl;
	event = "replay";
}

void BlackJack::onEnterState_standOff()
{
	cout << "Draw..." << endl;
	event = "replay";

}

void BlackJack::onEnterState_win()
{
	cout << "Participant " << turnIdx << " wins the game!..." << endl;
	event = "replay";
}

void BlackJack::onEnterState_restart()
{
	cout << "Do you wish to play again?..." << endl;
	collectPrevRoundCards();
	deck.clearDeck();
	event = "yes";
};

/* ================================================================ */


/* =========================== GUARDS ============================= */

//int BlackJack::getWinningPlayer() {
//	for (size_t i = 0; i < participants.size(); i++) {
//		if (participants[i]->getScore() == 21) {
//			return i;
//		}
//	}
//}

bool BlackJack::isAnyParticipant21() {
	for (size_t i = 0; i < participants.size(); i++) {
		if (participants[i]->getScore() == 21) {
			// set winner idx, becase this guard allows the transition 
			// to win state which utilises *blackjack->turnIdx to decide the winner
			return true;
		}
	}
	return false;
}

bool BlackJack::dealerHasLowestScore()
{
	// start with i=1 because index 0 is always the dealer.
	for (int i = 1; i < participants.size(); i++) {
		// check the players that still can play.
		if (participants[i]->getcanPlay())
		{
			// compare the score of the dealer with every player.
			if (getCurrentPlayerScore() >= participants[i]->getScore())
				// if the dealer has a higher score then any player that
				// can still play, return false
				return false;
		}
	}
	// if false is not returned above, it means that
	// dealer has the lowest score and still can play
	return true;
}

bool BlackJack::dealerAndPlayersHasSameScore() {
	for (int i = 1; i < participants.size(); i++) {
		if (participants[i]->getcanPlay())
		{
			if (getCurrentPlayerScore() != participants[i]->getScore())
				return false;
		}
	}
	return true;
}

bool BlackJack::dealerHasHighestScore()
{
	for (int i = 1; i < participants.size(); i++) {
		if (participants[i]->getcanPlay())
		{
			if (getCurrentPlayerScore() < participants[i]->getScore())
				return false;
		}
	}
	return true;
}

/* ================================================================ */

void BlackJack::setFSM() {
	fsm.setCurState("initialise");

	fsm.addState("initialise", setInitialiseState());
	fsm.addState("dealing", setDealingState());
	fsm.addState("playerTurn", setplayerTurnState());
	fsm.addState("dealerTurn", setdealerTurnState());
	fsm.addState("loss", setlossState());
	fsm.addState("standOff", setstandOffState());
	fsm.addState("win", setwinState());
	fsm.addState("restart", setrestartState());
	fsm.addState("quit", setquitState());
}

void BlackJack::setPlayers() {
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

Card BlackJack::popCard() {
	Card poppedCard = deck.activeDeck.back();
	deck.activeDeck.pop_back();
	return poppedCard;
}

void BlackJack::collectPrevRoundCards() {
	for (size_t i = 0; i < participants.size(); i++) {
		participants[i]->collectPrevRoundCards();
	}
}

void BlackJack::dealCards() {
	for (size_t i = 0; i < participants.size(); i++) {
		for (int j = 0; j < m_noOfCards; j++)
		{
			participants[i]->addCard(&popCard());
		}
	}
}

void BlackJack::hit(Participants* participant) {
	participant->addCard(&popCard());
}

void BlackJack::stand(Participants* participant)
{
	if (participant->getParticipantIdx() == 0)
	{
		cout << "Dealer stands..." << endl;
	}
	else {
		cout << "Player " << participant->getParticipantIdx() << " stands..." << endl;
	}
}