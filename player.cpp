#include "player.h"

Player::Player() 
{
	participantIdx = uniqueID++;
}

bool Player::isDealer()
{
	return false;
}


int Player::getParticipantIdx() const 
{
	return participantIdx;
}

bool Player::getcanPlay() const 
{
	return canPlay;
}

int Player::getScore() const
{
	return score;
}

void Player::collectPrevRoundCards() 
{
	cards.clear();
	score = 0;
}

void Player::printCards(const bool& isStateDealing) const 
{
	if (canPlay)
	{
		cout << "Player " << participantIdx << "'s cards are... " << endl;
	}
	for (size_t i = 0; i < cards.size(); i++)
	{
		if (canPlay)
		{
			cards[i].print();
		}

	}
	if (canPlay)
	{
		cout << "Total score: " << score << endl << endl;
	}
}

void Player::addCard(Card* card)
{
	cards.push_back(*card);
	score += card->val;

	adjustForAce(card);
}

void Player::adjustForAce(Card* card) 
{
	if (card->rank.compare("Ace") == 0 || m_hasAce) {
		m_hasAce = true;
		if (score > 21) {
			score -= 10;
			m_hasAce = false;
		}
	}
}

int Player::uniqueID = 1;