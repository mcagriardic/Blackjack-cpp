#include "BlackJack.h"

extern Guard* guard;
extern BlackJack* blackjack;

BlackJack::BlackJack(const int& _playerCount, const  int& _noOfDeck)
	: playerCount(_playerCount), noOfDecks(_noOfDeck)
{
	setFSM();
	setPlayers();
	guard->participants = participants;
};

//BlackJack::BlackJack() = default;

BlackJack::~BlackJack() {
	for (Participants* obj : participants)
		delete obj;
	participants.clear();
	delete guard;
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

void BlackJack::play() {

	string directive;

	// while there are transitions to make, run the while loop
	// only the "quit" state has no transitions
	while (!fsm.states[fsm.activeState].transitions.empty()) {
		for (size_t turnIdx_temp = 0; turnIdx_temp < participants.size(); turnIdx_temp++)
		{
			turnIdx = turnIdx_temp;
			guard->turnIdx = &turnIdx;
			fsm.evaluate("none");
		}
	}
}

void BlackJack::onEnterState_dealing() {
	deck.createDeck(noOfDecks);
	dealCards();
	// state should be inside FSM
	printCards(true);
	fsm.evaluate("dealt");
	
}

void BlackJack::onEnterState_playerTurn() {
	cout << "Player " << turnIdx << "'s turn..." << endl;
	cout << "Player " << turnIdx << ", do you wish to hit or stand?" << endl;

	if (participants[turnIdx]->getScore() < 17)
	{
		cout << "Player hits!" << endl << endl;
		hit(participants[turnIdx]);
		printCards();
		fsm.evaluate("hit");
	}
	else
	{
		cout << "Player stands!" << endl << endl;
		fsm.evaluate("stand");
	}
}

void BlackJack::onEnterState_dealerTurn() {
	cout << "Dealer's turn!" << endl;

	if (participants[turnIdx]->getScore() < 17)
	{
		cout << "Dealer hits!" << endl << endl;
		hit(participants[turnIdx]);
		printCards();
		fsm.evaluate("hit");
	}
	else
	{
		cout << "Dealer stands!" << endl << endl;
		fsm.evaluate("stand");
	}
}

void BlackJack::onEnterState_loss() 
{
	cout << "Participant " << turnIdx << " is out of the game..." << endl;

	if (participants.size() == 2) {
		if (turnIdx == 0) {
			cout << "Player has won the game!" << endl;
		}
		else {
			cout << "Dealer has won the game!" << endl;
		}
	}
	fsm.evaluate("replay");
}

void BlackJack::onEnterState_standOff()
{
	cout << "Draw..." << endl;
	fsm.evaluate("replay");
}

void BlackJack::onEnterState_win()
{
	cout << "Participant " << turnIdx << " wins the game!..." << endl;
	fsm.evaluate("replay");
}

void BlackJack::onEnterState_restart()
{
	cout << "Do you wish to play again?..." << endl;
	/*cin >> directive;*/
	collectPrevRoundCards();
	deck.clearDeck();
	fsm.evaluate("yes");
};

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