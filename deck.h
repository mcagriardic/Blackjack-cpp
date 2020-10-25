#pragma once

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

	void print() const {
		for (const Card& card : activeDeck)
		{
			card.print();
		}
	}

	void clearDeck() {
		activeDeck.clear();
	}

	void createDeck(int _noOfDecks) {
		for (int i = 0; i < _noOfDecks; i++)
		{
			for (const string& suit : m_suits)
			{
				for (const string& rank : m_ranks)
				{
					Card card(suit, rank, m_values[rank]);
					activeDeck.push_back(card);
				}
			}
		}

		shuffleDeck();
	}

private:
	void shuffleDeck() {
		srand((unsigned int)time(0));
		random_shuffle(activeDeck.begin(), activeDeck.end());
	}
};
