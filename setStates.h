#ifndef SETSTATES_H
#define SETSTATES_H

#include "FSM/state.h"
#include "game.h"


State setDealingState();
State setplayerTurnState();
State setdealerTurnState();
State setlossState();
State setstandOffState();
State setwinState();
State setRestartState();
State setquitState();

#endif