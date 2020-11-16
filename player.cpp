#include "player.h"

Player::Player() 
{
	participantIdx = uniqueID++;
	createHand();
}

void             Player::displayHand(Hand *hand, const bool& isStateDealing) const
{
	if (canPlay)
	{
		if (noOfHands > 1 && !hand->getisHandBust()) {
			cout << "Player " << participantIdx << ", hand " << hand->handIdx + 1 << ":" << endl << endl;
		}
		else if (!hand->getisHandBust()) {
			cout << "Player " << participantIdx << "'s cards are:" << endl << endl;
		}
		hand->displayHand(isStateDealing);
	}
}

bool             Player::isDealer()
{
	return false;
}

bool             Player::getisWinner() const {
	return isWinner;
}
bool             Player::getcanPlay() const
{
	return canPlay;
}
int              Player::getParticipantIdx() const 
{
	return participantIdx;
}
vector<Hand*>    Player::getHands() const {
	return hands;
}
int              Player::getnoOfHands() const {
	return noOfHands;
}
Hand*            Player::getHandByIdx(const int& handIdx) const {
	return hands[handIdx];
}
Hand*            Player::getLastHand() const{
	return hands.back();
}
bool             Player::gethasRefusedSplit() const {
	return hasRefusedSplit;
}

void             Player::setcanPlay(const bool& status) {
	canPlay = status;
}
void             Player::setisWinner(const bool& status) {
	isWinner = status;
}
void             Player::sethasRefusedSplit(const bool& status) {
	hasRefusedSplit = status;
}
void             Player::setisHandBust(const int& handIdx, const bool& status) {
	hands[handIdx]->setisHandBust(status);
}
void             Player::setnoOfHands(const int& _noOfHands) {
	noOfHands = _noOfHands;
}
void             Player::sethandIdx(const int& _handIdx) {
	handIdx = _handIdx;
}

void             Player::recalculateScore(Hand* hand) {
	hand->recalculateScore();
}
void             Player::createHand() {
	Hand* hand = new Hand(participantIdx, handIdx);
	hands.emplace_back(hand);
	handIdx++;
	noOfHands++;
}
void             Player::addCard(Hand* hand, Card* card)
{
	hand->addCard(card);
}
void             Player::collectPrevRoundCards() 
{
	for (int handIdx = 0; handIdx < hands.size(); handIdx++) {
		hands[handIdx]->clearHand();
		hands.resize(1);
	}
}

int              Player::uniqueID = 1;


