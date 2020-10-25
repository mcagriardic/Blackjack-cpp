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
	Deck deck;
	FSM fsm;
	size_t* turnIdx;
	string activeState = "dealing";
	vector<Participants*> participants;

	BlackJack(int _playerCount = 1, int _noOfDeck = 1);
	BlackJack();
	~BlackJack();
	void printDeck();
	void printCards(bool isStateDealing = false);
	void play();

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