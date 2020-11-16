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
				"split",
				[]() {return blackjack->canAnyPlayerSplit(); }
			),
			Transition(
				"dealt",
				"playerTurn",
				[]() {return !(blackjack->canAnyPlayerSplit());}
			)
		},
		[]() {blackjack->onEnterState_dealing();}
	);
}

State setsplitState() {
	return State(
		"split",
		{
			Transition(
				"yes",
				"splitYes",
				nullptr        // is directive yes can be used
			),
			Transition(
				"no",
				"splitNo",
				nullptr
			),
		},
		[]() {blackjack->onEnterState_split(); }
	);
}

State setsplitYesState() {
	return State(
		"splitYes",
		{
			Transition(
				"next",
				"split",
				[]() {return blackjack->canAnyPlayerSplit(); }
			),
			Transition(
				"next",
				"playerTurn",
				[]() {return !blackjack->canAnyPlayerSplit(); }
			),
		},
		[]() {blackjack->onEnterState_splitYes(); }
	);
}

State setsplitNoState() {
	return State(
		"splitNo",
		{
			Transition(
				"next",
				"Split",
				[]() {return blackjack->canAnyPlayerSplit(); }
			),
			Transition(
				"next",
				"playerTurn",
				[]() {return !blackjack->canAnyPlayerSplit(); }
			),
		},
		[]() {blackjack->onEnterState_splitNo(); }
	);
}

State setplayerTurnState()
{
	return State(
		"playerTurn",
		{
			Transition(
				"hit",
				"playerHit",
				[]() {return blackjack->isDirectiveHit(); }
			),
			Transition(
				"stand",
				"playerStand",
				[]() {return blackjack->isDirectiveStand(); }
			),
		},
		[]() {blackjack->onEnterState_playerTurn(); }
	);
}

State setplayerHitState() {
	return State(
		"playerHit",
		{
			Transition(
				"next",
				"playerTurn",
				[]() {return blackjack->getCurrentHandScore() < 21; }
			),
			Transition(
				"next",
				"handGoesBust",
				[]() {return blackjack->getCurrentHandScore() > 21; }
			),
			Transition(
				"next",
				"playerStand",
				[]() {return blackjack->getCurrentHandScore() == 21; }
			),
		},
		[]() {blackjack->onEnterState_playerHit(); }
	);
}

State setplayerStandState() {
	return State(
		"playerStand",
		{
			Transition(
				"next",
				"playerTurn",
				[]() {
					return (
						!blackjack->handsLeftToPlay()
							&&
						!blackjack->isNextPlayerDealer()
					); 
				},
				[]() {
					blackjack->setActivePlayer(
						blackjack->getNextPlayer()
					);
					blackjack->setActiveHand(0);
				}
			),
			// player still has hands to play, change the hand
			Transition(
				"next",
				"playerTurn",
				[]() {return blackjack->handsLeftToPlay(); },
				[]() {
					blackjack->setActiveHand(
						blackjack->getNextHand()
					);
				}
			),
			Transition(
				"next",
				"dealerTurn",
				[]() {
					return (
						!blackjack->handsLeftToPlay()
							&&
						blackjack->isNextPlayerDealer()
					);
				},
				[]() {
					blackjack->setActivePlayer(
						blackjack->getNextPlayer()
					);
					blackjack->setActiveHand(0);
				}
			),
		},
		[]() {blackjack->onEnterState_playerStand(); }
	);
}

State sethandGoesBustState() {
	return State(
		"handGoesBust",
		{
			Transition(
				"next",
				"outOfTheGame",
				[]() {return (!blackjack->handsLeftToPlay()
								&&
							  blackjack->isAllHandsBust()); 
				}
			),
			Transition(
				"next",
				"playerTurn",
				[]() {return (blackjack->handsLeftToPlay()
								&&
							  !blackjack->isAllHandsBust()); },
				[]() {
					blackjack->setActiveHand(
						blackjack->getNextHand()
					);
				}
			),
			Transition(
				"next",
				"playerTurn",
				[]() {return (!blackjack->handsLeftToPlay()
								&&
							  !blackjack->isAllHandsBust()); },
				[]() {
					blackjack->setActivePlayer(
						blackjack->getNextPlayer()
					);
					blackjack->setActiveHand(0);
				}
			),
		},
		[]() {blackjack->onEnterState_handGoesBust(); }
	);
}

State setoutOfTheGameState() {
	return State(
		"outOfTheGame",
		{
			Transition(
				"next",
				"playerTurn",
				[]() {return !blackjack->isNextPlayerDealer(); },
				[]() {
					blackjack->setActivePlayer(
						blackjack->getNextPlayer()
					);
					blackjack->setActiveHand(0);
				}
			),
			Transition(
				"next",
				"playersLose",
				[]() {return !blackjack->canAnyPlayerPlay(); }
			),
			Transition(
				"next",
				"dealerTurn",
				[]() {return (blackjack->isNextPlayerDealer() 
								&&
							  blackjack->canAnyPlayerPlay());},
				[]() {
					blackjack->setActivePlayer(
						blackjack->getNextPlayer()
					);
					blackjack->setActiveHand(0);
				}
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
				"hit",
				"dealerHit",
				[]() {return blackjack->isDirectiveHit(); }
			),
			Transition(
				"stand",
				"dealerStand",
				[]() {return blackjack->isDirectiveStand(); }
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

State setdealerHitState() {
	return State(
		"dealerHit",
		{
			Transition(
				"hit",
				"dealerTurn",
				[]() {
					return (
						blackjack->getCurrentHandScore() < 21
							||
						blackjack->getCurrentHandScore() == 21
					); 
				}
			),
			Transition(
				"hit",
				"dealerLose",
				[]() {return blackjack->getCurrentHandScore() > 21; }
			),
		},
		[]() {blackjack->onEnterState_dealerHit(); }
	);
}

State setdealerStandState() {
	return State(
		"dealerStand",
		{
			Transition(
				"stand",
				"dealerWin",
				[]() {
					return (
						!blackjack->playerHasHigherScore()
							&&
						!blackjack->dealerAndPlayersHasSameScore()
					); 
				}
			),
			Transition(
				"stand",
				"playerWin",
				[]() {return blackjack->playerHasHigherScore();}
			),
			Transition(
				"stand",
				"standOff",
				[]() {return blackjack->dealerAndPlayersHasSameScore(); }
			),
		},
		[]() {blackjack->onEnterState_dealerStand(); }
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
				"canPlayHandsWin",
				[]() {return blackjack->isDealerBust(); }
			),
			Transition(
				"next",
				"higherScoreHandsWin",
				[]() {return !blackjack->isDealerBust(); }
			)
		},
		[]() {blackjack->onEnterState_playerWin(); }
	);
}

State setcanPlayHandsWinState()
{
	return State(
		"canPlayHandsWin",
		{
			Transition(
				"replay",
				"restart",
				nullptr
			)
		},
		[]() {blackjack->onEnterState_canPlayHandsWin(); }
	);
}

State sethigherScoreHandsWinState()
{
	return State(
		"higherScoreHandsWin",
		{
			Transition(
				"replay",
				"restart",
				nullptr
			)
		},
		[]() {blackjack->onEnterState_higherScoreHandsWin(); }
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
