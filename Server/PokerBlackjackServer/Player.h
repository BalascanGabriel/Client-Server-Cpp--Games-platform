#pragma once

#include <iostream>
#include <string>
#include "Card.h"
#include "CardType.h"
#include <vector>
using namespace std;


class Player
{
private:
	vector<Card*> cards;
protected:
public:
	void add_card(Card* card);
};

