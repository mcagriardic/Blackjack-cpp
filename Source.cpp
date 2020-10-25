#include "BlackJack.h"

extern Game* game = new Game();

int main() {
	int noOfPlayers = 1;
	int noOfDecks = 1;
	BlackJack blackjack(noOfPlayers, noOfDecks);
	//game->blackjack = &blackjack;
	
	blackjack.play();

	cin.get();
}
