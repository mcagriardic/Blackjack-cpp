#include "game.h"

int Game::getCurrentPlayerScore()
{
	return participants[*turnIdx]->getScore();
}

bool Game::isAnyParticipant21() {
	for (size_t i = 0; i < participants.size(); i++) {
		if (participants[i]->getScore() == 21) {
			// set winner idx, becase this guard allows the transition 
			// to win state which utilises *blackjack->turnIdx to decide the winner
			*turnIdx = i;
			return true;
		}
	}
	return false;
}

bool Game::dealerHasLowestScore()
{
	// start with i=1 because index 0 is always the dealer.
	for (int i = 1; i < participants.size(); i++) {
		// check the players that still can play.
		if (participants[i]->getcanPlay())
		{
			// compare the score of the dealer with every player.
			if (getCurrentPlayerScore() >= participants[i]->getScore())
				// if the dealer has a higher score then any player that
				// can still play, return false
				return false;
		}
	}
	// if false is not returned above, it means that
	// dealer has the lowest score and still can play
	return true;
}

bool Game::dealerAndPlayersHasSameScore() {
	for (int i = 1; i < participants.size(); i++) {
		if (participants[i]->getcanPlay())
		{
			if (getCurrentPlayerScore() != participants[i]->getScore())
				return false;
		}
	}
	return true;
}

bool Game::dealerHasHighestScore()
{
	for (int i = 1; i < participants.size(); i++) {
		if (participants[i]->getcanPlay())
		{
			if (getCurrentPlayerScore() < participants[i]->getScore())
				return false;
		}
	}
	return true;
}


