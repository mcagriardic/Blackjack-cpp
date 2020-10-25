#pragma once

class Game {
public:
	BlackJack* blackjack;

	int getCurrentPlayerScore()
	{
		return blackjack->participants[*blackjack->turnIdx]->getScore();
	}

	bool isAnyParticipant21() {
		for (size_t i = 0; i < blackjack->participants.size(); i++) {
			if (blackjack->participants[i]->getScore() == 21) {
				// set winner idx, becase this guard allows the transition 
				// to win state which utilises turnIdx to decide the winner
				*blackjack->turnIdx = i;
				return true;
			}
		}
		return false;
	}

	bool dealerHasLowestScore() 
	{
		// start with i=1 because index 0 is always the dealer.
		for (int i = 1; i < blackjack->participants.size(); i++) {
			// check the players that still can play.
			if (blackjack->participants[i]->getcanPlay())
			{
				// compare the score of the dealer with every player.
				if (getCurrentPlayerScore() >= blackjack->participants[i]->getScore())
					// if the dealer has a higher score then any player that
					// can still play, return false
					return false; 
			}
		}
		// if false is not returned above, it means that
		// dealer has the lowest score and still can play
		return true;
	}

	bool dealerAndPlayersHasSameScore() {
		for (int i = 1; i < blackjack->participants.size(); i++) {
			if (blackjack->participants[i]->getcanPlay())
			{
				if (getCurrentPlayerScore() != blackjack->participants[i]->getScore())
					return false;
			}
		}
		return true;
	}

	bool dealerHasHighestScore()
	{
		for (int i = 1; i < blackjack->participants.size(); i++) {
			if (blackjack->participants[i]->getcanPlay())
			{
				if (getCurrentPlayerScore() < blackjack->participants[i]->getScore())
					return false;
			}
		}
		return true;
	}
};

Game* game = new Game();
