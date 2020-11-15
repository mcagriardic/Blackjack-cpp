# include "hand.h"

Hand::Hand(int& playerUniqueID, int& _handIdx)
	: idxBelongsToPlayer(playerUniqueID), handIdx(_handIdx)
	{
		;
	}

int  Hand::getScore() const {
	return score;
}
int  Hand::getIdxBelongsToPlayer() const {
	return idxBelongsToPlayer;
}
bool Hand::getisHandWinner() const {
	return isHandWinner;
}
bool Hand::getisHandBust() const {
	return isHandBust;
}
int  Hand::gethandIdx() const {
	return handIdx;
}

void Hand::sethasAce(const bool& status) {
	hasAce = status;
}
void Hand::setisHandBust(const bool& status) {
	isHandBust = status;
}
void Hand::setisHandWinner(const bool& status) {
	isHandWinner = status;
}

void Hand::addCard(Card* card){
	cards.push_back(*card);
	score += card->val;

	adjustForAce(card);
}
void Hand::recalculateScore() {
	score = 0;
	for (Card& card : cards) {
		score += card.val;
	}
}
void Hand::clearHand() {
	cards.clear();
	score = 0;
	sethasAce(false);
	setisHandBust(false);
}
void Hand::displayHand(const bool& isStateDealing) const
{
	if (!isHandBust)
	{
		for (size_t i = 0; i < cards.size(); i++)
		{
			cards[i].print();
		}
		cout << "Total score: " << score << endl << endl;
	}
}
void Hand::adjustForAce(Card* card)
{
	if (card->rank.compare("Ace") == 0 || hasAce) {
		hasAce = true;
		if (score > 21) {
			score -= 10;
			hasAce = false;
		}
	}
}