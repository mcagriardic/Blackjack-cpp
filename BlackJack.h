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
	int activeHandIdx;
	int activePlayerIdx;
	Deck deck;
	FSM fsm;
	vector<Participants*> participants;

	BlackJack     (const int& =1, const int& =1);
	~BlackJack    ();

	// prints
	void          printDeck();
	void          printCards(const bool& = false);

	// gets
	int           getWinnerIdx();
	int           getNextPlayer();
	int           getNextHand();
	int           getCurrentHandScore();
	vector<Hand*> getnotBustHands();
	vector<Hand*> getHandsScoreHigherThanDealerHand();
	int           getIdxPlayerCanSplit();
	int           getIdxHandCanSplit();

	// sets
public:
	void          setActivePlayer(const int&);
	void          setActiveHand(const int&);
	void          setcanPlay(const bool&);
	void          setisWinner(const bool&);
	void          setWinnerByIndex(const int&);
private:
	void          setFSM();
	void          setPlayers();

public:
	// resets
	void         resetAttributes();

	// --
	void         play();

	// state callbacks leads to below methods
	void         onEnterState_dealing();
	void		 onEnterState_split();
	void		 onEnterState_splitYes();
	void		 onEnterState_splitNo();
	void         onEnterState_playerTurn();
	void         onEnterState_playerHit();
	void         onEnterState_playerStand();
	void         onEnterState_handGoesBust();
	void         onEnterState_outOfTheGame();
	void         onEnterState_dealerTurn();
	void         onEnterState_dealerHit();
	void         onEnterState_dealerStand();
	void         onEnterState_playersLose();
	void         onEnterState_dealerWin();
	void         onEnterState_dealerLose();
	void         onEnterState_playerWin();
	void         onEnterState_canPlayHandsWin();
	void         onEnterState_higherScoreHandsWin();
	void         onEnterState_standOff();
	void         onEnterState_restart();

	// guards
	bool         canAnyPlayerSplit();
	bool         canAnyPlayerPlay();
	bool         isDirectiveHit();
	bool         isDirectiveStand();
	bool         handsLeftToPlay();
	bool         isNextPlayerDealer();
	bool         isDealerTurn();
	bool         playerHasHigherScore();
	bool         dealerAndPlayersHasSameScore();
	bool         isDealerBust();

private:
	void         split();
	Card         popCard();
	void         collectPrevRoundCards();
	void         dealCards();
	void         hit(Participants* participant);
	void         stand(Participants* participant);
};

#endif
