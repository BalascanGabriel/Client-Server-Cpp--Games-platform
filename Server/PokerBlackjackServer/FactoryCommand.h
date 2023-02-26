#pragma once
#include "CommandType.h"
#include "Response.h"
#include "ResponseCommand.h"
#include "CommandLogin.h"
#include "CommandRegister.h"
#include "CommandStartGame.h"
#include "CommandStartGameBlackJack.h"
#include "CommandStartGamePoker.h"
#include "CommandGetBudget.h"

class FactoryCommand
{
private:
	FactoryCommand();
public:

	static CommandType string_command_type(string str) {
		if (str.compare("op_login") == 0) {
			return CommandType::LOGIN;
		}
		if (str.compare("op_register") == 0) {
			return CommandType::REGISTER;
		}
		if (str.compare("op_start_game") == 0) {
			return CommandType::START_GAME;
		}
		if (str.compare("op_start_game_black_jack") == 0) {
			return CommandType::START_GAME_BLACK_JACK;
		}
		if (str.compare("op_start_game_poker") == 0) {
			return CommandType::START_GAME_POKER;
		}
		if (str.compare("op_budget") == 0) {
			return CommandType::GET_BUDGET;
		}

		
		return CommandType::ERROR_MESSAGE;

	}

	static Response* create_command(CommandType type, SOCKET& socket) {
		Response* response = NULL;
		switch (type) {
		case CommandType::FIRST:
			response = new ResponseCommand(socket);
			break;
		case CommandType::LOGIN:
			response = new CommandLogin(socket);
			break;
		case CommandType::REGISTER:
			response = new CommandRegister(socket);
			break;
		case CommandType::START_GAME:
			response = new CommandStartGame(socket);
			break;
		case CommandType::START_GAME_BLACK_JACK:
			response = new CommandStartGameBlackJack(socket);
			break;
		case CommandType::START_GAME_POKER:
			response = new CommandStartGamePoker(socket);
			break;
		case CommandType::GET_BUDGET:
			response = new CommandGetBudget(socket);
			break;
		}
		return response;
	}
};


