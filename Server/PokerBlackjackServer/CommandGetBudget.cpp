#include "CommandGetBudget.h"


CommandGetBudget::CommandGetBudget(SOCKET& socket) : Response(socket)
{
	this->comType = CommandType::GET_BUDGET;
}

std::string* CommandGetBudget::execute()
{

	std::cout << "GETTING BUDGET" << std::endl;

	std::string* user_id = this->get_message(this->socket);
	std::stringstream ss(*user_id);
	int user_id_int;
	ss >> user_id_int;
	std::cout << "CLIENT / USER ID = " << user_id_int << std::endl;

	int budget = UserDB::get_player_budget(user_id_int);
	std::cout << "SENDING BUGET: " << budget << std::endl;
	this->send_message(this->socket, "" + to_string(budget));
	//// std::string* email = this->get_message(this->socket);
	//std::string* password = this->get_message(this->socket);
	//User user_nou(*username, *password);
	//int id_user = UserDB::insert_user(user_nou);
	//std::cout << "REGISTERING WITH: " << *username << " PASSWORD: " << *password << std::endl;
	//this->send_message(this->socket, "" + to_string(id_user));

	return nullptr;
}