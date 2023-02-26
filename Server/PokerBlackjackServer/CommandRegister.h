#pragma once

#include "Response.h"
#include "User.h"
#include "UserDB.h"

class CommandRegister : public Response
{
private:
public:
	CommandRegister(SOCKET& socket);
	std::string* execute();
};



