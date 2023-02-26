#pragma once

#include "Response.h"

class ResponseCommand : public Response
{
private:
public:
	ResponseCommand(SOCKET& socket);
	std::string* execute();
};

