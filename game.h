#ifndef GAME_H
#define GAME_H

#include "participants.h"

class Game {
public:
	string* activeState;
	size_t* turnIdx;
	vector<Participants*> participants;

	int getCurrentPlayerScore();
	bool isAnyParticipant21();
	bool dealerHasLowestScore();
	bool dealerAndPlayersHasSameScore();
	bool dealerHasHighestScore();
};

#endif