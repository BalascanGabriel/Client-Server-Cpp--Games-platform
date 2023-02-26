#pragma once

#include "Response.h"
#include "CardType.h"
#include "Card.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include "DeckUtil.h"
#include "UserDB.h"
#include <sstream>

class CommandStartGamePoker : public Response
{
public:
	CommandStartGamePoker(SOCKET& socket);
	std::string* execute();

	bool iteratie_joc(std::vector<Card*>& deck);
};

