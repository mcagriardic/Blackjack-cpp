#include "setStates.h"

extern Guard* guard;
extern BlackJack* blackjack;

// stateTag
// stateTransitions 
// there should at most 1 transition, i need to add a nullptr

State setInitialiseState() {
	return State(
		"initialise",
		{
			Transition("none", "dealing", nullptr)
		},
		nullptr
	);
}

State setDealingState()
{
	return State(
		"dealing",      
		{                
			Transition("dealt", "win", []() {return guard->isAnyParticipant21(); }),
			Transition("dealt", "playerTurn", []() {return !guard->isAnyParticipant21(); })
		},
		[]() {blackjack->onEnterState_dealing();}
	);
}

State setplayerTurnState()
{
	return State(
		"playerTurn",
		{
			Transition("hit", "win", []() {return guard->getCurrentPlayerScore() == 21; }),
			Transition("hit", "playerTurn", []() {return guard->getCurrentPlayerScore() < 21; }),
			Transition("stand", "dealerTurn", nullptr),
			Transition("hit", "loss", []() {return guard->getCurrentPlayerScore() > 21; })
		},
		[]() {blackjack->onEnterState_playerTurn(); }
	);
}

State setdealerTurnState()
{
	return State(
		"dealerTurn",
		{
			Transition("hit", "loss", []() {return guard->getCurrentPlayerScore() > 21; }),
			Transition("hit", "dealerTurn", []() {return guard->getCurrentPlayerScore() < 21; }),
			Transition("stand", "loss", []() {return guard->dealerHasLowestScore(); }),
			Transition("stand", "standOff", []() {return guard->dealerAndPlayersHasSameScore(); }),
			Transition("stand", "win", []() {return guard->dealerHasHighestScore(); }),
			Transition("hit", "win", []() {return guard->getCurrentPlayerScore() == 21; })
		},
		[]() {blackjack->onEnterState_dealerTurn(); }
	);
}

State setlossState()
{
	return State(
		"loss",
		{
			Transition("replay", "restart", nullptr)
		},
		[]() {blackjack->onEnterState_loss(); }
	);
}

State setstandOffState()
{
	return State(
		"standOff",
		{
			Transition("replay", "restart", nullptr)
		},
		[]() {blackjack->onEnterState_standOff(); }
	);
}

State setwinState()
{
	return State(
		"win",
		{
			Transition("replay", "restart", nullptr)
		},
		[]() {blackjack->onEnterState_win(); }
	);
}

State setrestartState()
{
	return State(
		"restart",
		{
			Transition("yes", "dealing", nullptr),
			Transition("no", "quit", nullptr)
		},
		[]() {blackjack->onEnterState_restart(); }
	);
}

State setquitState()
{
	return State(
		"quit",
		{},
		nullptr
	);
}
