#include "card.h"

Card::Card(
	string suit,string rank,int val)
	: suit(suit), rank(rank), val(val)
{;}

void Card::print() const {
	std::cout << rank << '-' << val << " of " << suit << std::endl;
}