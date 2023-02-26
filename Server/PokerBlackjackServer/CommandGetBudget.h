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
#include <sstream>

class CommandGetBudget : public Response
{
public:
	CommandGetBudget(SOCKET& socket);
	std::string* execute();

	
};

