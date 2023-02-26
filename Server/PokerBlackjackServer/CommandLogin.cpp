#include "CommandLogin.h"

CommandLogin::CommandLogin(SOCKET& socket) : Response(socket)
{
	this->comType = CommandType::LOGIN;
}

std::string* CommandLogin::execute()
{
	std::string* username = this->get_message(this->socket);
	std::string* password = this->get_message(this->socket);
	std::cout << "Client wants to login with : " << *username << " " << *password << std::endl;

	int buget = -1;
	int rezultat = UserDB::login(*username, *password, buget);
	std::string mesaj_login = to_string(rezultat) + " " + to_string(buget);
	std::cout << "Mesaj login for client: " << mesaj_login << std::endl;
	this->send_message(this->socket, mesaj_login);
	return NULL;
}
