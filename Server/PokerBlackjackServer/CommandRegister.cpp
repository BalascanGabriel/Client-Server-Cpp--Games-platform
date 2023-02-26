#include "CommandRegister.h"

CommandRegister::CommandRegister(SOCKET& socket) : Response(socket)
{
	this->comType = CommandType::REGISTER;
}

std::string* CommandRegister::execute()
{
	std::string* username = this->get_message(this->socket);
	// std::string* email = this->get_message(this->socket);
	std::string* password = this->get_message(this->socket);
	User user_nou(*username, *password);
	int id_user = UserDB::insert_user(user_nou);
	std::cout << "REGISTERING WITH: " << *username << " PASSWORD: " << *password << std::endl;
	std::string message_client = "REGISTER " + to_string(id_user);

	std::cout << "Message client: " << message_client << std::endl;
	this->send_message(this->socket, message_client);
	std::cout << "AFTER MESSAGE SENT" << std::endl;

	return nullptr;
}
