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

	BlackJack     (const int& _playerCount=1, const int& _noOfDeck=1);
	~BlackJack    ();

	// prints
	void          printDeck();
	void          printCards(const bool& isStateDealing = false);

	// gets
	int           getWinnerIdx();
	int           getNextPlayer();
	int           getCurrentPlayerScore();
	int           getIdxPlayerWith21();
	int           getIdxPlayerWithHighestScore();
	vector<int>   getIdxCanPlayPlayers();
	vector<int>   getPlayerScores();

	// sets
public:
	void          setActivePlayer(const int& _activePlayerIdx);
	void          setcanPlay(const bool& status);
	void          setisWinner(const bool& status);
	void          setWinnerByIndex(const int& participantIdx);
private:
	void          setFSM();
	void          setPlayers();

public:
	// resets
	void         resetcanPlay();
	void         resetisWinner();

	// --
	void         takeDirective();
	void         play();

	// state callbacks leads to below methods
	void         onEnterState_dealing();
	void         onEnterState_playerTurn();
	void         onEnterState_outOfTheGame();
	void         onEnterState_dealerTurn();
	void         onEnterState_playersLose();
	void         onEnterState_dealerWin();
	void         onEnterState_dealerLose();
	void         onEnterState_playerWin();
	void         onEnterState_standOff();
	void         onEnterState_directWin();
	void         onEnterState_singleplayerWin();
	void         onEnterState_multiplePlayersWin();
	void         onEnterState_restart();

	// guards
	bool         canAnyPlayerPlay();
	bool         isNextPlayerDealer();
	bool         isDealerTurn();
	bool         isAnyParticipant21();
	bool         playerHasHigherScore();
	bool         dealerAndPlayersHasSameScore();
	bool         playersHasSameScore();

private:
	Card         popCard();
	void         collectPrevRoundCards();
	void         dealCards();
	void         hit(Participants* participant);
	void         stand(Participants* participant);
};

#endif
