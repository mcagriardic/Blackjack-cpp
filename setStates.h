#ifndef SETSTATES_H
#define SETSTATES_H

#include "FSM/state.h"
#include "BlackJack.h"

State setInitialiseState();
State setDealingState();
State setsplitState();
State setsplitYesState();
State setsplitNoState();
State setplayerTurnState();
State setplayerHitState();
State setplayerStandState();
State sethandGoesBustState();
State setoutOfTheGameState();
State setdealerTurnState();
State setplayersLoseState();
State setdealerHitState();
State setdealerStandState();
State setdealerWinState();
State setdealerLoseState();
State setplayerWinState();
State setcanPlayHandsWinState();
State sethigherScoreHandsWinState();
State setstandOffState();
State setrestartState();
State setquitState();

#endif
