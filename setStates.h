#ifndef SETSTATES_H
#define SETSTATES_H

#include "FSM/state.h"
#include "BlackJack.h"

State setInitialiseState();
State setDealingState();
State setplayerTurnState();
State setoutOfTheGameState();
State setdealerTurnState();
State setplayersLoseState();
State setdealerWinState();
State setdealerLoseState();
State setplayerWinState();
State setstandOffState();
State setdirectWinState();
State setsinglePlayerWinState();
State setmultiplePlayersWinState();
State setrestartState();
State setquitState();

#endif
