#pragma once
#include "Response.h"
class CommandStartGame : public Response
{
public:
	CommandStartGame(SOCKET& socket);
	std::string* execute();
};

