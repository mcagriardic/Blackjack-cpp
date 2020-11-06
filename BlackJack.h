#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "dealer.h"
#include "player.h"
#include "FSM/FSM.h"
#include "setStates.h"

class BlackJack{
private:
	int m_noOfCards = 2;
public:
	int playerCount;
	int noOfDecks;
	string directive;
	string event;
	int activePlayerIdx;
	Deck deck;
	FSM fsm;
	vector<Participants*> participants;

	BlackJack(const int& _playerCount=1, const int& _noOfDeck=1);
	~BlackJack();
	void printDeck();
	void printCards(const bool& isStateDealing = false);
	int  getCurrentPlayerScore();
	vector<int> getCanPlayPlayers();
	void resetcanPlay();
	void resetisWinner();
	void takeDirective();
	int getWinnerIdx();
	void play();

	// state callbacks leads to below methods
	void onEnterState_dealing();
	void onEnterState_playerTurn();
	void onEnterState_dealerTurn();
	void onEnterState_loss();
	void onEnterState_standOff();
	void onEnterState_win();
	void onEnterState_restart();

	// transition actions
	void setActivePlayer(const int& _activePlayerIdx);
	int  getNextPlayer();
	void setcanPlay(const bool& status);
	void setisWinner(const bool& status);


	// guards
	bool isDealerTurn();
	bool isAnyParticipant21();
	bool dealerHasLowestScore();
	bool dealerAndPlayersHasSameScore();
	bool dealerHasHighestScore();

private:
	void setFSM();

	void setPlayers();
	Card popCard();
	void collectPrevRoundCards();
	void dealCards();
	void hit(Participants* participant);
	void stand(Participants* participant);
};

#endif










/*              Replace for manual play           */
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