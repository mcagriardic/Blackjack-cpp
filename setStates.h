#ifndef SETSTATES_H
#define SETSTATES_H

#include "FSM/state.h"
#include "BlackJack.h"

State setInitialiseState();
State setDealingState();
State setplayerTurnState();
State setdealerTurnState();
State setlossState();
State setstandOffState();
State setwinState();
State setrestartState();
State setquitState();

#endif
