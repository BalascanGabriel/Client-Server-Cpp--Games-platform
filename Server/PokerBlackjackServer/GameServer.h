#pragma once

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Response.h"
#include <vector>
#include "FactoryCommand.h"
#include "CommandType.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")


#define DEFAULT_PORT "9000"

using namespace std;

class GameServer
{
private:
	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;
	vector<Response*> commands_from_client;
public:

	SOCKET& get_socket();
	GameServer();
	// start game, end game
	// login logout
	// register
	void start_client_communication();

	void start();

	void register_user();
	void login_user();
	void start_game_poker();
	void start_game_blackjack();
};

