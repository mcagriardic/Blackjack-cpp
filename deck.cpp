#include "deck.h"
#include <chrono>
#include <thread>

void Deck::print() const {
	for (const Card& card : activeDeck)
	{
		card.print();
	}
}

void Deck::clearDeck() {
	activeDeck.clear();
}

void Deck::createDeck(const int& _noOfDecks) {
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
	using namespace std::this_thread;
	using std::chrono::system_clock;
	sleep_until(system_clock::now() + 0.5s);
	shuffleDeck();
}

void Deck::shuffleDeck() {
	srand((unsigned int)time(0));
	random_shuffle(activeDeck.begin(), activeDeck.end());
}