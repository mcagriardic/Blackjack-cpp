#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <time.h> 
#include <tuple>

#include "card.h"
#include "deck.h"
#include "participants.h"
#include "player.h"
#include "dealer.h"
#include "BlackJack.h"

using namespace std;

int main() {
	int noOfPlayers = 2;
	int noOfDecks = 1;
	BlackJack game(noOfPlayers, noOfDecks);

	game.play();
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