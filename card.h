#pragma once

using namespace std;

class Card {

public:
	string suit;
	string rank;
	int val;

	Card(
		string suit = "",
		string rank = "",
		int val = 0
	)
		: suit(suit), rank(rank), val(val) {
		;
	}

	void print() const {
		cout << rank << '-' << val << " of " << suit << endl;
	}

};