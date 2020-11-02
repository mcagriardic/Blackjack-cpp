#include "BlackJack.h"

extern BlackJack* blackjack = new BlackJack(1,1);

int main() {
	blackjack->play();
	cin.get();
}
