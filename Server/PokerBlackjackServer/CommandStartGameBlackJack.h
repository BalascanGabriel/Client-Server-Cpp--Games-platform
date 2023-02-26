#pragma once
#include "Response.h"
#include "CardType.h"
#include "Card.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "DeckUtil.h"
#include <sstream>
#include "UserDB.h"

class CommandStartGameBlackJack : public Response
{
public:
	CommandStartGameBlackJack(SOCKET& socket);
	std::string* execute();

	bool iteratie_joc(std::vector<Card*>& deck);
};

