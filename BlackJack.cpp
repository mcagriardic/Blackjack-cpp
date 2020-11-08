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

/* =========================== PRINTS =========================== */

void BlackJack::printDeck() {
	deck.print();
}

void BlackJack::printCards(const bool& isStateDealing) {
	for (int i = 0; i < participants.size(); i++) {
		participants[i]->printCards(isStateDealing);
	}
}

/* =========================== GETS =========================== */

int BlackJack::getWinnerIdx() {
	for (size_t i = 0; i < participants.size(); i++) {
		if (participants[i]->getisWinner()) {
			return i;
		}
	}
}

int BlackJack::getNextPlayer() {
	if (activePlayerIdx < playerCount) {
		return activePlayerIdx + 1;
	}
	else {
		return 0;
	}
}

int BlackJack::getCurrentPlayerScore()
{
	return participants[activePlayerIdx]->getScore();
}

int BlackJack::getIdxPlayerWith21() {
	for (size_t i = 0; i < participants.size(); i++) {
		if (participants[i]->getScore() == 21) {
			return i;
		}
	}
}

int BlackJack::getIdxPlayerWithHighestScore()
{
	int tempHighestScore = -1;
	int tempHighestScoreIdx;
	for (size_t i = 1; i < participants.size(); i++) {
		if (participants[i]->getcanPlay()) {
			if (participants[i]->getScore() > tempHighestScore) {
				tempHighestScore = participants[i]->getScore();
				tempHighestScoreIdx = i;
			}
		}
	}
	return tempHighestScoreIdx;
}

vector<int> BlackJack::getIdxCanPlayPlayers() {
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

vector<int> BlackJack::getPlayerScores() {
	vector<int> playerScores;
	for (int i = 1; i < participants.size(); i++) {
		if (participants[i]->getcanPlay())
		{
			playerScores.emplace_back(participants[i]->getScore());
		}
	}
	return playerScores;
}

/* =========================== SETS =========================== */

void BlackJack::setActivePlayer(const int& _activePlayerIdx) {
	activePlayerIdx = _activePlayerIdx;
}

void BlackJack::setcanPlay(const bool& status)
{
	participants[activePlayerIdx]->setcanPlay(status);
}

void BlackJack::setisWinner(const bool& status)
{
	participants[activePlayerIdx]->setisWinner(status);
}

void BlackJack::setWinnerByIndex(const int& participantIdx) {
	participants[participantIdx]->setisWinner(true);
}

void BlackJack::setFSM() {
	fsm.setCurState("initialise");

	fsm.addState("initialise", setInitialiseState());
	fsm.addState("dealing", setDealingState());
	fsm.addState("playerTurn", setplayerTurnState());
	fsm.addState("outOfTheGame", setoutOfTheGameState());
	fsm.addState("dealerTurn", setdealerTurnState());
	fsm.addState("playersLose", setplayersLoseState());
	fsm.addState("dealerWin", setdealerWinState());
	fsm.addState("dealerLose", setdealerLoseState());
	fsm.addState("playerWin", setplayerWinState());
	fsm.addState("standOff", setstandOffState());
	fsm.addState("directWin", setdirectWinState());
	fsm.addState("singlePlayerWin", setsinglePlayerWinState());
	fsm.addState("multiplePlayersWin", setmultiplePlayersWinState());
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

/* =========================== RESETS =========================== */

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

/* ================================================================ */

void BlackJack::takeDirective()
{
	cout << "Player " << activePlayerIdx << "'s turn..." << endl;
	cout << "Player " << activePlayerIdx << ", do you wish to hit or stand?" << endl;
	cin >> directive;
}

void BlackJack::play() {
	fsm.postEventToQueue("next");

	// while there are transitions to make, run the while loop
	// only the "quit" state has no transitions
	while (!fsm.states[fsm.activeState].transitions.empty()) {
		fsm.processQueuedEvents();
		//takeDirective();
		//fsm.postEventToQueue(directive);
	}
}

/* =========================== STATE CALLBACKS =========================== */

void BlackJack::onEnterState_dealing() {
	fsm.cleartransitionHistory();
	deck.createDeck(noOfDecks);
	dealCards();
	printCards(true);
	setActivePlayer(1);
	fsm.postEventToQueue("dealt");
}

void BlackJack::onEnterState_playerTurn() {
	cout << "Player " << activePlayerIdx << "'s turn..." << endl;
	cout << "Player " << activePlayerIdx << ", do you wish to hit or stand?" << endl;

	if (getCurrentPlayerScore() < 17) {
		directive = "hit";
	}
	else {
		directive = "stand";
	}

	if (directive.compare("hit") == 0)
	{
		hit(participants[activePlayerIdx]);
		printCards();
		fsm.postEventToQueue(directive);
		//fsm.postEventToQueue(directive);
		//fsm.processQueuedEvents();
	}
	else if (directive.compare("stand") == 0)
	{
		stand(participants[activePlayerIdx]);
		fsm.postEventToQueue(directive);
		//fsm.postEventToQueue(directive);
		//fsm.processQueuedEvents();
	}
}

void BlackJack::onEnterState_outOfTheGame()
{
	cout << "Player " << activePlayerIdx << " is out of the game..." << endl << endl;
	setcanPlay(false);
	//setActivePlayer(getNextPlayer());
	fsm.postEventToQueue("next");
}

void BlackJack::onEnterState_dealerTurn() {
	cout << "Dealer's turn!" << endl;

	if (participants[activePlayerIdx]->getScore() < 17)
	{
		hit(participants[activePlayerIdx]);
		printCards();
		fsm.postEventToQueue("hit");
	}
	else
	{
		fsm.postEventToQueue("stand");
	}
}

void BlackJack::onEnterState_playersLose() {
	cout << "Players Lose!" << endl;
	fsm.postEventToQueue("next");
}

void BlackJack::onEnterState_dealerWin() {
	setWinnerByIndex(0);
	cout << "Dealer Wins!" << endl;
	fsm.postEventToQueue("replay");
}

void BlackJack::onEnterState_dealerLose() {
	cout << "Dealer is above 21, bust!..." << endl;
	fsm.postEventToQueue("next");
}

void BlackJack::onEnterState_playerWin() {
	// since we can only enter this state when it is dealer's turn
	// setcanPlay(false) here changes the canPlay attribute of
	// the dealer 
	setcanPlay(false);
	fsm.postEventToQueue("next");
}

void BlackJack::onEnterState_standOff()
{
	cout << "Draw..." << endl;
	printCards();
	fsm.postEventToQueue("replay");
}

void BlackJack::onEnterState_directWin() {
	int winnerIdx = getIdxPlayerWith21();
	setWinnerByIndex(winnerIdx);
	string toDisplay = (winnerIdx == 0) ? "Dealer" : "Player " + to_string(winnerIdx);
	cout << toDisplay << " wins the game!..." << endl << endl;
	fsm.postEventToQueue("replay");
}

void BlackJack::onEnterState_singleplayerWin() {
	int winnerIdx = getIdxPlayerWithHighestScore();
	setWinnerByIndex(winnerIdx);
	cout << "Player " << winnerIdx << " wins the game!..." << endl << endl;
	fsm.postEventToQueue("replay");
}

void BlackJack::onEnterState_multiplePlayersWin() {
	vector<int> winnerIdxs = getIdxCanPlayPlayers();
	for (int& idx : winnerIdxs) {
		setWinnerByIndex(idx);
		cout << "Player " << idx << " wins the game" << endl;
	}
	cout << endl;
	fsm.postEventToQueue("replay");
}

//void BlackJack::onEnterState_win()
//{
//	if (participants[getWinnerIdx()]->isDealer()) {
//		cout << "Dealer wins the game!..." << endl;
//	}
//	else
//	{
//		cout << "Player " << getWinnerIdx() << " wins the game!..." << endl;
//	} 
//	printCards();
//	fsm.postEventToQueue("replay");
//}

//void BlackJack::onEnterState_loss() 
//{
//	if (participants[activePlayerIdx]->isDealer()) 
//	{
//		cout << "Dealer is out of the game!..." << endl;
//		for (int i = 0; i < participants.size(); i++) {
//			if (participants[i]->getcanPlay())
//			{
//				cout << "Player " << i << " wins the game!..." << endl;
//			}
//		}
//		cout << endl;
//	}
//	else if (!participants[activePlayerIdx]->isDealer()) 
//	{
//		if (getCanPlayPlayers().size() > 0) 
//		{
//			cout << "Player " << activePlayerIdx << " is out of the game!..." << endl;
//		}
//		else 
//		{
//			cout << "Dealer wins the game!..." << endl;
//		}
//	}
//	printCards();
//	fsm.postEventToQueue("replay");
//}

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

/* =========================== GUARDS ============================= */

bool BlackJack::canAnyPlayerPlay() {
	for (size_t i = 1; i < participants.size(); i++) {
		if (participants[i]->getcanPlay()) {
			return true;
		}
	}
	return false;
}

bool BlackJack::isNextPlayerDealer() {
	return participants[getNextPlayer()]->isDealer();
}

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

bool BlackJack::playerHasHigherScore()
{	
	// at least 1 player has higher score
	// start with i=1 because index 0 is always the dealer.
	for (int i = 1; i < participants.size(); i++) {
		// check the players that still can play.
		if (participants[i]->getcanPlay())
		{
			// compare dealer with every player
			if (getCurrentPlayerScore() <= participants[i]->getScore())
				// if even 1 player is higher than dealer,
				// then playerWins -> at least 1 player has higher score
				// than dealer
				return true;
		}
	}
	// if we cannot enter above if condition
	// this means dealer has higher score than the rest
	return false;
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

bool BlackJack::playersHasSameScore() {
	// get the scores of players who can play
	vector<int> playerScores = getPlayerScores();

	// check if playerScores vector has the same values
	if (equal(playerScores.begin() + 1, playerScores.end(), playerScores.begin()))
	{
		return true;
	}
	return false;
}

//bool BlackJack::dealerHasHigherScore()
//{
//	for (int i = 1; i < participants.size(); i++) {
//		if (participants[i]->getcanPlay())
//		{
//			if (getCurrentPlayerScore() <= participants[i]->getScore())
//				return false;
//		}
//	}
//	return true;
//}

/* ================================================================ */

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
	int participantIdx = participant->getParticipantIdx();
	string toDisplay = (participantIdx == 0) ? "Dealer" : "Player " + to_string(participantIdx);
	cout << toDisplay << " hits..." << endl << endl;

	participant->addCard(&popCard());
}

void BlackJack::stand(Participants* participant)
{
	int participantIdx = participant->getParticipantIdx();
	string toDisplay = (participantIdx == 0) ? "Dealer" : "Player " + to_string(participantIdx);
	cout << toDisplay << " stands..." << endl << endl;
}



















/* ====================== TRANSITION ACTIONS ====================== */



/* ================================================================ */














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