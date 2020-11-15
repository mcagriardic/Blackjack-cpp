#include "player.h"

Player::Player() 
{
	participantIdx = uniqueID;
	createHand();
	uniqueID++;
}

void             Player::displayHand(Hand *hand, const bool& isStateDealing) const
{
	if (canPlay)
	{
		if (noOfHands > 1 && !hand->getisHandBust()) {
			cout << "Player " << participantIdx << ", hand " << hand->handIdx + 1 << ":" << endl << endl;
		}
		else {
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
//void Player::sethasAce(const bool& status) {
//	hasAce = status;
//}

void             Player::recalculateScore(Hand* hand) {
	hand->recalculateScore();
}
void             Player::createHand() {
	Hand* hand = new Hand(uniqueID, handIdx);
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
	}
}

int              Player::uniqueID = 1;


