#include "BlackJack.h"

extern          BlackJack* blackjack;

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

void            BlackJack::printDeck() {
	deck.print();
}
void            BlackJack::printCards(const bool& isStateDealing) {
	for (int playerIdx = 0; playerIdx < participants.size(); playerIdx++) {
		vector<Hand*> hands = participants[playerIdx]->getHands();
		for (int handIdx = 0; handIdx < hands.size(); handIdx++) {
			participants[playerIdx]->displayHand(hands[handIdx], isStateDealing);
		}
	}
}

/* =========================== GETS =========================== */

int             BlackJack::getWinnerIdx() {
	for (size_t i = 0; i < participants.size(); i++) {
		if (participants[i]->getisWinner()) {
			return i;
		}
	}
}
int             BlackJack::getNextPlayer() {
	if (activePlayerIdx < playerCount) {
		return activePlayerIdx + 1;
	}
	else {
		return 0;
	}
}
int             BlackJack::getNextHand() {

	return activeHandIdx + 1;
}
int             BlackJack::getCurrentHandScore()
{
	return participants[activePlayerIdx]->getHandByIdx(activeHandIdx)->score;
}
vector<Hand*>   BlackJack::getnotBustHands() {
	vector<Hand*> notBustHands;
	for (int playerIdx = 1; playerIdx < participants.size(); playerIdx++) {
		for (Hand* hand : participants[playerIdx]->getHands()) {
			if (!hand->getisHandBust())
			{
				notBustHands.push_back(hand);
			}
		}
	}
	return notBustHands;
}
vector<Hand*>   BlackJack::getHandsScoreHigherThanDealerHand() {

	vector<Hand*> playerHandsHigherThanDealer;

	// dealer will always have one hand
	int dealerScore = participants[0]->getHandByIdx(0)->getScore();

	for (int playerIdx = 1; playerIdx < participants.size(); playerIdx++) {
		for (Hand* hand : participants[playerIdx]->getHands()) {
			if (
				dealerScore < hand->getScore() 
					&&
				!hand->getisHandBust()
			)
			{
				playerHandsHigherThanDealer.push_back(hand);
			}
		}
	}
	return playerHandsHigherThanDealer;
}
int             BlackJack::getIdxPlayerCanSplit() {
	for (size_t playerIdx = 1; playerIdx < participants.size(); playerIdx++) {
		if (!participants[playerIdx]->gethasRefusedSplit())
		{
			vector<Hand*> hands = participants[playerIdx]->getHands();
			for (int handIdx = 0; handIdx < hands.size(); handIdx++) {
				if (hands[handIdx]->cards[0].rank.compare(
					hands[handIdx]->cards[1].rank
				) == 0)
				{
					return playerIdx;
				}
			}
		}
	}
}
int             BlackJack::getIdxHandCanSplit() {
	for (size_t playerIdx = 1; playerIdx < participants.size(); playerIdx++) {
		if (!participants[playerIdx]->gethasRefusedSplit())
		{
			vector<Hand*> hands = participants[playerIdx]->getHands();
			for (int handIdx = 0; handIdx < hands.size(); handIdx++) {
				if (hands[handIdx]->cards[0].rank.compare(hands[handIdx]->cards[1].rank) == 0)
				{
					return handIdx;
				}
			}
		}
	}

}

/* =========================== SETS =========================== */

void            BlackJack::setActivePlayer(const int& _activePlayerIdx) {
	activePlayerIdx = _activePlayerIdx;
}
void            BlackJack::setActiveHand(const int& _activeHandIdx) {
	activeHandIdx = _activeHandIdx;
}
void            BlackJack::setcanPlay(const bool& status)
{
	participants[activePlayerIdx]->setcanPlay(status);
}
void            BlackJack::setisWinner(const bool& status)
{
	participants[activePlayerIdx]->setisWinner(status);
}
void            BlackJack::setWinnerByIndex(const int& participantIdx) {
	participants[participantIdx]->setisWinner(true);
}
void            BlackJack::setFSM() {
	fsm.setCurState("initialise");

	fsm.addState("initialise",           setInitialiseState());
	fsm.addState("dealing",              setDealingState());
	fsm.addState("split",                setsplitState());
	fsm.addState("splitYes",             setsplitYesState());
	fsm.addState("splitNo",              setsplitNoState());
	fsm.addState("playerTurn",           setplayerTurnState());
	fsm.addState("playerHit",            setplayerHitState());
	fsm.addState("playerStand",          setplayerStandState());
	fsm.addState("handGoesBust",         sethandGoesBustState());
	fsm.addState("outOfTheGame",         setoutOfTheGameState());
	fsm.addState("dealerTurn",           setdealerTurnState());
	fsm.addState("playersLose",          setplayersLoseState());
	fsm.addState("dealerHit",            setdealerHitState());
	fsm.addState("dealerStand",          setdealerStandState());
	fsm.addState("dealerWin",            setdealerWinState());
	fsm.addState("dealerLose",           setdealerLoseState());
	fsm.addState("playerWin",            setplayerWinState());
	fsm.addState("canPlayHandsWin",      setcanPlayHandsWinState());
	fsm.addState("higherScoreHandsWin",  sethigherScoreHandsWinState());
	fsm.addState("standOff",             setstandOffState());
	fsm.addState("restart",              setrestartState());
	fsm.addState("quit",                 setquitState());
}
void            BlackJack::setPlayers() {
	Participants* dealer = new Dealer();
	participants.push_back(dealer);
	for (int i = 0; i < playerCount; i++)
	{
		Participants* player = new Player();
		participants.push_back(player);
	}
};

/* =========================== RESETS =========================== */

void            BlackJack::resetAttributes() {
	for (int i = 0; i < participants.size(); i++) {
		participants[i]->setisWinner(false);
		participants[i]->setcanPlay(true);
		participants[i]->sethasRefusedSplit(false);
		participants[i]->collectPrevRoundCards();
	}
}

/* ================================================================ */

void            BlackJack::play() {
	fsm.postEventToQueue("next");

	// while there are transitions to make, run the while loop
	// only the "quit" state has no transitions
	while (!fsm.states[fsm.activeState].transitions.empty()) {
		fsm.processQueuedEvents();
		//cin >> directive;
		//fsm.postEventToQueue(directive);
	}
}

/* =========================== STATE CALLBACKS =========================== */

void            BlackJack::onEnterState_dealing() {
	fsm.cleartransitionHistory();
	deck.createDeck(noOfDecks);
	dealCards();
	printCards(true);
	setActivePlayer(1);
	setActiveHand(0);
	fsm.postEventToQueue("dealt");
}
void            BlackJack::onEnterState_split() {
	cout << "Player " << getIdxPlayerCanSplit() << " do you wish to split?" << endl;
	fsm.postEventToQueue("yes");
}
void            BlackJack::onEnterState_splitYes() {
	setActivePlayer(getIdxPlayerCanSplit());
	setActiveHand(getIdxHandCanSplit());
	cout << "Splitting..." << endl << endl;
	split();
	fsm.postEventToQueue("next");
}
void            BlackJack::onEnterState_splitNo() {
	cout << "Player " << getIdxPlayerCanSplit() << " has refused to split..." << endl;
	participants[getIdxPlayerCanSplit()]->sethasRefusedSplit(false);
	fsm.postEventToQueue("next");
}
void            BlackJack::onEnterState_playerTurn() {
	cout << "Player " << activePlayerIdx << "'s turn..." << endl;
	string toDisplay = activeHandIdx != 0 ? " for hand " + to_string(activeHandIdx + 1) : "";
	cout << "Player " << activePlayerIdx << toDisplay <<", do you wish to hit or stand?" << endl;

	directive = (getCurrentHandScore() < 17) ? "hit" : "stand";
	fsm.postEventToQueue(directive);
}
void            BlackJack::onEnterState_playerHit() {
	string toDisplay = activeHandIdx != 0 ? (" for hand " + to_string(activeHandIdx + 1)) : "";
	cout << "Player " << activePlayerIdx << " hits" << toDisplay << "!..." <<endl << endl;
	hit(participants[activePlayerIdx]);
	printCards();
	fsm.postEventToQueue("next");
}
void            BlackJack::onEnterState_playerStand() {
	cout << "Player " << activePlayerIdx << " stands!..." << endl << endl;
	stand(participants[activePlayerIdx]);
	printCards();
	fsm.postEventToQueue("next");
}
void            BlackJack::onEnterState_handGoesBust() {
	int noOfHands = participants[activePlayerIdx]->getnoOfHands();

	if (noOfHands > 1){
		cout << "Player " << activePlayerIdx << ": Hand " << activeHandIdx + 1 << " is over 21, hand goes bust!..." << endl;
	}
	else {
		cout << "Hand is above 21!..." << endl;
	}

	participants[activePlayerIdx]->setisHandBust(
		activeHandIdx,
		true
	);

	fsm.postEventToQueue("next");
}
void            BlackJack::onEnterState_outOfTheGame()
{
	cout << "Player " << activePlayerIdx << " has no hands left to play!... Player " <<activePlayerIdx << " is out of the game!..." << endl << endl;
	setcanPlay(false);
	fsm.postEventToQueue("next");
}
void            BlackJack::onEnterState_dealerTurn() {
	cout << "Dealer's turn!" << endl;
	directive = (getCurrentHandScore() < 17) ? "hit" : "stand";
	fsm.postEventToQueue(directive);
}
void            BlackJack::onEnterState_dealerHit() {
	cout << "Dealer hits!..." << endl;
	hit(participants[activePlayerIdx]);
	printCards();
	fsm.postEventToQueue("hit");

}
void            BlackJack::onEnterState_dealerStand() {
	cout << "Dealer stands!..." << endl;
	stand(participants[activePlayerIdx]);
	fsm.postEventToQueue("stand");
}
void            BlackJack::onEnterState_playersLose() {
	cout << "Players Lose!" << endl;
	fsm.postEventToQueue("next");
}
void            BlackJack::onEnterState_dealerWin() {
	setWinnerByIndex(0);
	cout << "Dealer Wins!" << endl << endl;
	fsm.postEventToQueue("replay");
}
void            BlackJack::onEnterState_dealerLose() {
	cout << "Dealer is above 21, bust!..." << endl;
	participants[0]->setisHandBust(0 ,true);
	setcanPlay(false);
	fsm.postEventToQueue("next");
}
void            BlackJack::onEnterState_playerWin() 
{
	string toDisplay = (playerCount == 1) ? "Player wins!" : "Players win!";
	cout << toDisplay << endl;
	fsm.postEventToQueue("next");
}
void            BlackJack::onEnterState_canPlayHandsWin() {
	vector<Hand*> winnerHands = getnotBustHands();

	for (Hand* winnerHand : winnerHands) {

		int handBelongsToPlayer = winnerHand->getIdxBelongsToPlayer();
		setWinnerByIndex(handBelongsToPlayer);
		winnerHand->setisHandWinner(true);

		if (participants[handBelongsToPlayer]->getnoOfHands() > 1)
		{
			cout << "Player " << handBelongsToPlayer << ": Hand " << winnerHand->gethandIdx() + 1 << " beats dealer's hand!..." << endl;
		}
		else
		{
			cout << "Player " << handBelongsToPlayer << " beats the dealer!..." << endl;
		}
	}
	cout << endl;
	fsm.postEventToQueue("replay");
}
void            BlackJack::onEnterState_higherScoreHandsWin() {

	vector<Hand*> winnerHands = getHandsScoreHigherThanDealerHand();

	for (Hand* winnerHand : winnerHands) {

		int handBelongsToPlayer = winnerHand->getIdxBelongsToPlayer();
		setWinnerByIndex(handBelongsToPlayer);
		winnerHand->setisHandWinner(true);

		if (participants[handBelongsToPlayer]->getnoOfHands() > 1)
		{
			cout << "Player " << handBelongsToPlayer << ": Hand " << winnerHand->gethandIdx() + 1 << " beats dealer's hand!..." << endl;
		}
		else
		{
			cout << "Player " << handBelongsToPlayer << " beats the dealer!..." << endl;
		}
	}
	cout << endl;
	fsm.postEventToQueue("replay");
}
void            BlackJack::onEnterState_standOff()
{
	cout << "Draw..." << endl << endl;
	printCards();
	fsm.postEventToQueue("replay");
}
void            BlackJack::onEnterState_restart()
{
	cout << "Do you wish to play again?..." << endl << endl;
	collectPrevRoundCards();
	deck.clearDeck();
	resetAttributes();
	directive = "";
	fsm.postEventToQueue("yes");
};

/* ================================================================ */

/* =========================== GUARDS ============================= */

bool            BlackJack::canAnyPlayerSplit() {
	for (size_t i = 1; i < participants.size(); i++) {
		// if player has not refused to split
		// this is to prevent asking the same 
		// player again
		if (!participants[i]->gethasRefusedSplit())
		{
			vector<Hand*> hands = participants[i]->getHands();
			for (int handIdx = 0; handIdx < hands.size(); handIdx++) {
				if (hands[handIdx]->cards[0].rank.compare(
					hands[handIdx]->cards[1].rank
				) == 0)
				{
					return true;
				}
			}
		}
	}
	return false;
}
bool            BlackJack::canAnyPlayerPlay() {
	for (size_t i = 1; i < participants.size(); i++) {
		if (participants[i]->getcanPlay()) {
			return true;
		}
	}
	return false;
}
bool            BlackJack::isDirectiveHit() {
	return directive.compare("hit") == 0;
}
bool            BlackJack::isDirectiveStand() {
	return directive.compare("stand") == 0;
}
bool            BlackJack::handsLeftToPlay() {
	int handCount = participants[activePlayerIdx]->getnoOfHands();
	// activeHandIdx starts with 0
	if (activeHandIdx < handCount - 1) {
		return true;
	}
	return false;
}
bool            BlackJack::isNextPlayerDealer() {
	return participants[getNextPlayer()]->isDealer();
}
bool            BlackJack::isDealerTurn() {
	return participants[activePlayerIdx]->isDealer();
}
bool            BlackJack::playerHasHigherScore()
{	
	for (int playerIdx = 1; playerIdx < participants.size(); playerIdx++) {
		if (participants[playerIdx]->getcanPlay())
		{
			for (Hand* hand : participants[playerIdx]->getHands()) {
				if (getCurrentHandScore() < hand->getScore())
					return true;
			}
		}
	}
	return false;
}
bool            BlackJack::dealerAndPlayersHasSameScore() {
	for (int playerIdx = 1; playerIdx < participants.size(); playerIdx++) {
		if (participants[playerIdx]->getcanPlay())
		{
			for (Hand* hand : participants[playerIdx]->getHands()) {
				if (getCurrentHandScore() != hand->getScore())
					return false;
			}

		}
	}
	return true;
}
bool            BlackJack::isDealerBust() {
	return      participants[0]->getHandByIdx(0)->getisHandBust();
}

/* ================================================================ */

void            BlackJack::split() {
	participants[activePlayerIdx]->createHand();

	Hand* hand_to_split = participants[activePlayerIdx]->getHandByIdx(activeHandIdx);
	Hand* hand_to_append = participants[activePlayerIdx]->getLastHand();

	hand_to_append->cards.emplace_back(hand_to_split->cards.back());
	hand_to_split->cards.pop_back();

	participants[activePlayerIdx]->addCard(hand_to_split, &popCard());
	participants[activePlayerIdx]->addCard(hand_to_append, &popCard());

	participants[activePlayerIdx]->recalculateScore(hand_to_split);
	participants[activePlayerIdx]->recalculateScore(hand_to_append);
	printCards();
	setActivePlayer(1);
	setActiveHand(0);
}
Card            BlackJack::popCard() {
	Card poppedCard = deck.activeDeck.back();
	deck.activeDeck.pop_back();
	return poppedCard;
}
void            BlackJack::collectPrevRoundCards() {
	for (size_t i = 0; i < participants.size(); i++) {
		participants[i]->collectPrevRoundCards();
	}
}
void            BlackJack::dealCards() {
	for (size_t i = 0; i < participants.size(); i++) {
		Hand* hand = participants[i]->getHandByIdx(0);
		for (int j = 0; j < m_noOfCards; j++)
		{
			participants[i]->addCard(hand, &popCard());
		}
	} 
}
void            BlackJack::hit(Participants* participant) {
	Hand* hand = participant->getHandByIdx(activeHandIdx);
	participant->addCard(hand, &popCard());
}
void            BlackJack::stand(Participants* participant)
{
	;
}
