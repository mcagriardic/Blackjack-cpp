#include <iostream>
#include "dealer.h"

Dealer::Dealer() {
	createHand();
}

void Dealer::displayHand(Hand *hand, const bool& isStateDealing) const {
	if (canPlay)
	{
		cout << "Dealer's cards are... " << endl << endl;
		hand->displayHand(isStateDealing);
	}
}

bool Dealer::isDealer()
{
	return true;
}

bool             Dealer::getisWinner() const {
	return isWinner;
}
bool             Dealer::getcanPlay() const {
	return canPlay;
}
int              Dealer::getParticipantIdx() const {
	return uniqueID;
}
vector<Hand*>    Dealer::getHands() const {
	return hands;
}
int              Dealer::getnoOfHands() const {
	return noOfHands;
}
Hand*            Dealer::getHandByIdx(const int& handIdx) const {
	return hands[handIdx];
}
Hand*            Dealer::getLastHand() const {
	return hands.back();
}
bool             Dealer::gethasRefusedSplit() const {
	return NULL;
}

void             Dealer::setcanPlay(const bool& status) {
	canPlay = status;
}
void             Dealer::setisWinner(const bool& status) {
	isWinner = status;
}
void             Dealer::sethasRefusedSplit(const bool& status) {
	NULL;
}
void             Dealer::setisHandBust(const int& handIdx, const bool& status) {
	hands[handIdx]->setisHandBust(status);
}

void             Dealer::recalculateScore(Hand* hand) {
	NULL;
}
void             Dealer::createHand() {
	Hand* hand = new Hand(uniqueID, handIdx);
	hands.emplace_back(hand);
}
void             Dealer::addCard(Hand* hand, Card* card)
{
	hand->addCard(card);
}
void             Dealer::collectPrevRoundCards()
{
	for (int handIdx = 0; handIdx < hands.size(); handIdx++) {
		hands[handIdx]->clearHand();
	}
}
