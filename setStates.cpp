#include "setStates.h"

extern BlackJack* blackjack;

State setInitialiseState() {
	return State(
		"initialise",
		{
			Transition(
				"next",
				"dealing",
				nullptr
			)
		},
		nullptr
	);
}

State setDealingState()
{
	return State(
		"dealing",      
		{                
			Transition(
				"dealt",
				"directWin",
				[]() {return blackjack->isAnyParticipant21(); } // removed the transition action
			),
			Transition(
				"dealt",
				"playerTurn",
				[]() {return !(blackjack->isAnyParticipant21());}
			)
		},
		[]() {blackjack->onEnterState_dealing();}
	);
}

State setplayerTurnState()
{
	return State(
		"playerTurn",
		{
			Transition(
				"hit",
				"outOfTheGame",
				[]() {return blackjack->getCurrentPlayerScore() > 21; }
			),
			Transition(
				"hit",
				"playerTurn",
				[]() {return blackjack->getCurrentPlayerScore() < 21; }
			),
			Transition(
				"hit",
				"directWin",
				[]() {return blackjack->getCurrentPlayerScore() == 21; } // removed the transition action
			),
			Transition(
				"stand",
				"playerTurn",
				[]() {return !(blackjack->isNextPlayerDealer()); },
				[]() {blackjack->setActivePlayer(blackjack->getNextPlayer()); } // necessary
			),
			Transition(
				"stand",
				"dealerTurn",
				[]() {return blackjack->isNextPlayerDealer(); },
				[]() {blackjack->setActivePlayer(blackjack->getNextPlayer()); } // necessary
			),
		},
		[]() {blackjack->onEnterState_playerTurn(); }
	);
}

State setoutOfTheGameState() {
	return State(
		"outOfTheGame",
		{
			Transition(
				"next",
				"playerTurn",
				[]() {return !(blackjack->isNextPlayerDealer()); },
				[]() {blackjack->setActivePlayer(blackjack->getNextPlayer()); } // necessary
			),
			Transition(
				"next",
				"dealerTurn",
				[]() {return (blackjack->isNextPlayerDealer() 
								&&
							  blackjack->canAnyPlayerPlay());},
				[]() {blackjack->setActivePlayer(blackjack->getNextPlayer()); } // necessary
			),
			Transition(
				"next",
				"playersLose",
				[]() {return !(blackjack->canAnyPlayerPlay()); }
			)
		},
		[]() {blackjack->onEnterState_outOfTheGame(); }
	);
}

State setdealerTurnState()
{
	return State(
		"dealerTurn",
		{
			Transition(
				"stand",
				"dealerWin",
				[]() {return !(blackjack->playerHasHigherScore()); } // removed the transition action
			),
			Transition(
				"hit",
				"dealerLose",
				[]() {return blackjack->getCurrentPlayerScore() > 21; } // can be placed inside dealerLose
			),
			Transition(
				"stand",
				"playerWin",
				[]() {return blackjack->playerHasHigherScore(); } // removed the transition action 
			),
			Transition(
				"stand",
				"standOff",
				[]() {return blackjack->dealerAndPlayersHasSameScore(); }
			),
			Transition(
				"hit",
				"dealerTurn",
				[]() {return blackjack->getCurrentPlayerScore() < 21; }
			),

			Transition(
				"hit",
				"directWin",
				[]() {return blackjack->getCurrentPlayerScore() == 21; } // removed the transition action
			)
		},
		[]() {blackjack->onEnterState_dealerTurn(); }
	);
}

State setplayersLoseState()
{
	return State(
		"playersLose",
		{
			Transition(
				"next",
				"dealerWin",
				nullptr
			)
		},
		[]() {blackjack->onEnterState_playersLose(); }
	);
}

State setdealerWinState()
{
	return State(
		"dealerWin",
		{
			Transition(
				"replay",
				"restart",
				nullptr
			)
		},
		[]() {blackjack->onEnterState_dealerWin(); }
	);
}

State setdealerLoseState()
{
	return State(
		"dealerLose",
		{
			Transition(
				"next",
				"playerWin",
				nullptr
			)
		},
		[]() {blackjack->onEnterState_dealerLose(); }
	);
}

State setplayerWinState()
{
	return State(
		"playerWin",
		{
			Transition(
				"next",
				"singlePlayerWin",
				[]() {return !(blackjack->playersHasSameScore()); }
			),
		Transition(
				"next",
				"multiplePlayersWin",
				[]() {return blackjack->playersHasSameScore(); }   
			)
		},
		[]() {blackjack->onEnterState_playerWin(); }
	);
}

State setstandOffState()
{
	return State(
		"standOff",
		{
			Transition(
				"replay",
				"restart",
				nullptr
			)
		},
		[]() {blackjack->onEnterState_standOff(); }
	);
}

State setdirectWinState()
{
	return State(
		"directWin",
		{
			Transition(
				"replay",
				"restart",
				nullptr
			)
		},
		[]() {blackjack->onEnterState_directWin(); }
	);
}

State setsinglePlayerWinState()
{
	return State(
		"singlePlayerWin",
		{
			Transition(
				"replay",
				"restart",
				nullptr
			)
		},
		[]() {blackjack->onEnterState_singleplayerWin(); }
	);
}

State setmultiplePlayersWinState()
{
	return State(
		"multiplePlayersWin",
		{
			Transition(
				"replay",
				"restart",
				nullptr
			)
		},
		[]() {blackjack->onEnterState_multiplePlayersWin(); }
	);
}

State setrestartState()
{
	return State(
		"restart",
		{
			Transition(
				"yes",
				"dealing",
				nullptr
			),
			Transition(
				"no",
				"quit",
				nullptr
			)
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
