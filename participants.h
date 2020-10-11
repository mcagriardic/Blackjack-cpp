#pragma once

class Participants {
public:
	virtual void printInfo() const = 0;
	virtual bool addCard(Card* cards) = 0;
	virtual void printCards(bool isGame = false) const = 0;
	virtual int getPlayerIdx() const = 0;
	virtual bool getcanPlay() const = 0;
	virtual bool getisWinner() const = 0;
	virtual int getScore() const = 0;
	virtual void setStand(bool stand) = 0;
	virtual bool getStand() const = 0;
};