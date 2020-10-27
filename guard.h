#ifndef GAME_H
#define GAME_H

#include "participants.h"

class Guard {
public:
	// refactor turnIdx into something that makes sense -> activeplayer
	size_t* turnIdx;
	vector<Participants*> participants;

	int getCurrentPlayerScore();
	bool isAnyParticipant21();
	bool dealerHasLowestScore();
	bool dealerAndPlayersHasSameScore();
	bool dealerHasHighestScore();
	// whenever entering the state, this should be triggered as a callback from the state class
	//int getWinningPlayer();
};

#endif