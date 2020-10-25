#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <time.h> 

using namespace std;

class Card {

public:
	string suit;
	string rank;
	int val;

	Card(string suit = "", string rank = "", int val = 0);
	void print() const;
};

#endif