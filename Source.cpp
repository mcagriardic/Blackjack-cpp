#include "BlackJack.h"

extern Guard* guard = new Guard();
extern BlackJack* blackjack = new BlackJack();

int main() {
	int noOfPlayers = 1;
	int noOfDecks = 1;
	blackjack->play();
	cin.get();
}
