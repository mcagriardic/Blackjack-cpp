#include "setStates.h"

extern Game* game;

State setDealingState()
{
	return State(
		"dealing",      // stateTag
		{               // stateTransitions  
			Transition("dealt", "win", []() {return game->isAnyParticipant21(); }),
			Transition("dealt", "playerTurn", nullptr)
		}
	);
}

State setplayerTurnState()
{
	return State(
		"playerTurn",
		{
			Transition("hit", "win", []() {return game->getCurrentPlayerScore() == 21; }),
			Transition("hit", "playerTurn", []() {return game->getCurrentPlayerScore() < 21; }),
			Transition("stand", "dealerTurn", nullptr),
			Transition("hit", "loss", []() {return game->getCurrentPlayerScore() > 21; })
		}
	);
}

State setdealerTurnState()
{
	return State(
		"dealerTurn",
		{
			Transition("hit", "loss", []() {return game->getCurrentPlayerScore() > 21; }),
			Transition("hit", "dealerTurn", []() {return game->getCurrentPlayerScore() < 21; }),
			Transition("stand", "loss", []() {return game->dealerHasLowestScore(); }),
			Transition("stand", "standOff", []() {return game->dealerAndPlayersHasSameScore(); }),
			Transition("stand", "win", []() {return game->dealerHasHighestScore(); }),
			Transition("hit", "win", []() {return game->getCurrentPlayerScore() == 21; })
		}
	);
}

State setlossState()
{
	return State(
		"loss",
		{
			Transition("replay", "restart", nullptr)
		}
	);
}

State setstandOffState()
{
	return State(
		"standOff",
		{
			Transition("replay", "restart", nullptr)
		}
	);
}

State setwinState()
{
	return State(
		"win",
		{
			Transition("replay", "restart", nullptr)
		}
	);
}

State setRestartState()
{
	return State(
		"restart",
		{
			Transition("yes", "dealing", nullptr),
			Transition("no", "quit", nullptr)
		}
	);
}

State setquitState()
{
	return State(
		"quit",
		{}
	);
}
