#ifndef DECK_H
#define DECK_H

#include "card.h"

class Deck {
private:
	string m_suits[4] = { "Hearts", "Diamonds", "Spades", "Clubs" };

	string m_ranks[13] = {
		"Two", "Three", "Four", "Five", "Six",
		"Seven", "Eight", "Nine", "Ten", "Jack",
		"Queen", "King", "Ace"
	};

	map<string, int> m_values = {
		{"Two", 2}, {"Three", 3}, {"Four", 4}, {"Five", 5},
		{"Six", 6}, {"Seven", 7}, {"Eight", 8}, {"Nine", 9},
		{"Ten", 10}, {"Jack", 10}, {"Queen", 10}, {"King", 10},
		{"Ace", 11}
	};

public:
	vector<Card> activeDeck;
		
	void print() const;
	void clearDeck();
	void createDeck(const int& _noOfDecks);

private:
	void shuffleDeck();
};

#endif