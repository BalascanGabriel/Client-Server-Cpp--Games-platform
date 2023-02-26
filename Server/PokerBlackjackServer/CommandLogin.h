#pragma once
#include "Response.h"

#include <string>
#include <iostream>
#include "User.h"
#include "UserDB.h"


class CommandLogin : public Response
{
public:
	CommandLogin(SOCKET& socket);
	std::string* execute();
};

