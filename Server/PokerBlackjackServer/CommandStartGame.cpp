#include "CommandStartGame.h"

CommandStartGame::CommandStartGame(SOCKET& socket) : Response(socket)
{
	this->comType = CommandType::START_GAME;
}

std::string* CommandStartGame::execute()
{
	return nullptr;
}
