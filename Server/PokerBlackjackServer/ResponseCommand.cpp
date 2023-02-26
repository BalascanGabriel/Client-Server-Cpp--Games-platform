#include "ResponseCommand.h"

ResponseCommand::ResponseCommand(SOCKET& socket): Response(socket)
{
}

std::string* ResponseCommand::execute()
{
	// asteapta un string de la user 
	// string care reprezinta urmatoarea comanda
	std::string* client_message = this->get_message(this->socket);
	return client_message;
}
