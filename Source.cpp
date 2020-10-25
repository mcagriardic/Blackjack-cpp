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













//const Deck deck;
//deck.Print();

//vector<int> test = { 1,2,3,4 };
//int lastElem = test.back();
//test.pop_back();
//cout << lastElem << endl;

//for (const int& elem : test) {
//	cout << elem << endl;
//}

//int i = 2;
//while (i--) {
//	cout << "test" << endl;
//}



	//void dealCards(Participants participant) {
	//	int noOfCards = 2;
	//	while (noOfCards--) {
	//		Card poppedCard = deck.back();
	//		deck.pop_back();
	//	}
	//}

	//Participants* participants = new Participants();
	//participants->PrintIdx();

	//Player* p = new Player(1);

	//Participants* player = p;
	//player->PrintIdx();

// 	vector<Participants*> participants = game->getParticipants();
//for (int i = 0; i < participants.size(); i++) {
//	participants[i]->printCards(false);
//}