#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include "GameServer.h"
#include "Response.h"
#include "ResponseCommand.h"
#include "CommandLogin.h"

#include "User.h"
#include "UserDB.h"
#include <vector>
#include <stdlib.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "9000"

using namespace std;


int __cdecl main(void)
{

  
    GameServer server; // ready for port communication
    server.start_client_communication();  // recv send
    server.start(); // start work with client


   

    system("pause");
    return 0;
}