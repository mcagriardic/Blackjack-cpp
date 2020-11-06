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

int  BlackJack::getCurrentPlayerScore()
{
	return participants[activePlayerIdx]->getScore();
}

vector<int> BlackJack::getCanPlayPlayers() {
	vector<int> canPlayPlayers;
	// start with i=1 here because if the dealer cannot play,
	// then the game is over.
	for (int i = 1; i < participants.size(); i++) {
		if (participants[i]->getcanPlay()) {
			canPlayPlayers.push_back(i);
		}
	}
	return canPlayPlayers;
}

void BlackJack::resetcanPlay() {
	for (int i = 0; i < participants.size(); i++) {
		participants[i]->setcanPlay(true);
	}
}

void BlackJack::resetisWinner() {
	for (int i = 0; i < participants.size(); i++) {
		participants[i]->setisWinner(false);
	}
}

int BlackJack::getWinnerIdx() {
	for (size_t i = 0; i < participants.size(); i++) {
		if (participants[i]->getisWinner()) {
			return i;
		}
	}
}

void BlackJack::takeDirective()
{
	cout << "Player " << activePlayerIdx << "'s turn..." << endl;
	cout << "Player " << activePlayerIdx << ", do you wish to hit or stand?" << endl;
	cin >> directive;
}

void BlackJack::play() {
	fsm.postEventToQueue("none");

	// while there are transitions to make, run the while loop
	// only the "quit" state has no transitions
	while (!fsm.states[fsm.activeState].transitions.empty()) {
		fsm.processQueuedEvents();
		takeDirective();
		fsm.postEventToQueue(directive);
	}
}

/* =========================== STATE CALLBACKS =========================== */

void BlackJack::onEnterState_dealing() {
	deck.createDeck(noOfDecks);
	dealCards();
	printCards(true);
	setActivePlayer(1);
	fsm.postEventToQueue("dealt");
}

void BlackJack::onEnterState_playerTurn() {
	if (directive.compare("hit") == 0)
	{
		hit(participants[activePlayerIdx]);
		printCards();
	}
	else if (directive.compare("stand") == 0)
	{
		stand(participants[activePlayerIdx]);
	}
}

void BlackJack::onEnterState_dealerTurn() {
	cout << "Dealer's turn!" << endl;

	if (participants[activePlayerIdx]->getScore() < 17)
	{
		cout << "Dealer hits!" << endl << endl;
		hit(participants[activePlayerIdx]);
		printCards();
		fsm.postEventToQueue("hit");
	}
	else
	{
		cout << "Dealer stands!" << endl << endl;
		fsm.postEventToQueue("stand");
	}
}

void BlackJack::onEnterState_loss() 
{
	if (participants[activePlayerIdx]->isDealer()) 
	{
		cout << "Dealer is out of the game!..." << endl;
		for (int i = 0; i < participants.size(); i++) {
			if (participants[i]->getcanPlay())
			{
				cout << "Player " << i << " wins the game!..." << endl;
			}
		}
		cout << endl;
	}
	else if (!participants[activePlayerIdx]->isDealer()) 
	{
		if (getCanPlayPlayers().size() > 0) 
		{
			cout << "Player " << activePlayerIdx << " is out of the game!..." << endl;
		}
		else 
		{
			cout << "Dealer wins the game!..." << endl;
		}
	}

	printCards();
	fsm.postEventToQueue("replay");
}

void BlackJack::onEnterState_standOff()
{
	cout << "Draw..." << endl;
	printCards();
	fsm.postEventToQueue("replay");
}

void BlackJack::onEnterState_win()
{
	if (participants[activePlayerIdx]->isDealer()) {
		cout << "Dealer wins the game!..." << endl;
	}
	else
	{
		cout << "Player" << getWinnerIdx() << " wins the game!..." << endl;
	} 
	printCards();
	fsm.postEventToQueue("replay");
}

void BlackJack::onEnterState_restart()
{
	cout << "Do you wish to play again?..." << endl;
	collectPrevRoundCards();
	deck.clearDeck();
	resetcanPlay();
	resetisWinner();
	directive = "";
	fsm.postEventToQueue("yes");
};

/* ================================================================ */


/* ====================== TRANSITION ACTIONS ====================== */

void BlackJack::setActivePlayer(const int& _activePlayerIdx) {
	activePlayerIdx = _activePlayerIdx;
}

int BlackJack::getNextPlayer() {
	if (activePlayerIdx < playerCount) {
		return activePlayerIdx + 1;
	}
	else {
		return 0;
	}
}

void BlackJack::setcanPlay(const bool& status)
{
	participants[activePlayerIdx]->setcanPlay(status);
}

void BlackJack::setisWinner(const bool& status)
{
	participants[activePlayerIdx]->setisWinner(status);
}

/* ================================================================ */


/* =========================== GUARDS ============================= */

bool BlackJack::isDealerTurn() {
	return participants[activePlayerIdx]->isDealer();
}

bool BlackJack::isAnyParticipant21() {
	for (size_t i = 0; i < participants.size(); i++) {
		if (participants[i]->getScore() == 21) {
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
			if (participants[0]->getScore() != participants[i]->getScore())
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
	Participants* dealer = new Dealer();
	participants.push_back(dealer);

	for (int i = 0; i < playerCount; i++)
	{
		Participants* player = new Player();
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
	if (participant->getParticipantIdx() == 0) 
	{
		cout << "Dealer hits..." << endl << endl;
	}
	else
	{
		cout << "Player " << participant->getParticipantIdx() << " hits..." << endl << endl;
	}
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

































// have your user input here

// performs transition
//event = "";
//cin >> event;


// have an explicit event next for immediate transition

// if the state you progressed is a type of immediate transition, call it directly. "" is next from the notes
//fsm.evaluate("");

// event based transition -- there will be input
// immediate transition -- you need to code this into
// your state machine -- you can use general event next

// FSM should hold the next

// insert the event in the queue

// take the event from the queue, evaluate make a transition or not

// dealt event into the queue and now it contains 1 item -- call evaluate. Function takes event out of the queue and calls the evaluate function with the event that had just been taken from the queue

// next step --> evaluate will take another event from the queue, now the queue is empty. Move to PlayerTurn. We are not moving to next state because the queue is empty, because dealt enforces to move

// You post the event to the queue, but you are not blocking the event