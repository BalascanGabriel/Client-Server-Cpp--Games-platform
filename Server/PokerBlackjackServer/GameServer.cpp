#include "GameServer.h"



SOCKET& GameServer::get_socket()
{
    return this->ClientSocket;
}

GameServer::GameServer()
{

    cout << "===================SERVER===============" << endl;
    WSADATA wsaData;
    int iResult;

   
    

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    
 

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return ;
    }

    cout << "PANA AICI A FOST PORNIREA SERVER-ului" << endl;
}

void GameServer::start_client_communication()
{
    
    // Accept a client socket
    this->ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return ;
    }

    // No longer need server socket
    closesocket(ListenSocket);


    cout << "AICI PRIMIM DATE DE LA CLIENTI" << endl;
   
        
 // } while (iResult > 0);

    // shutdown the connection since we're done

    //cout << "PARTEA ASTA DE COD SE EXECUTA DUPA CE SERVER-ul SI CLIENTUL AU TERMINAT DE VORBIT" << endl;
    //iResult = shutdown(ClientSocket, SD_SEND);
    //if (iResult == SOCKET_ERROR) {
    //    printf("shutdown failed with error: %d\n", WSAGetLastError());
    //    closesocket(ClientSocket);
    //    WSACleanup();
    //    return;
    //}

    //// cleanup
    //closesocket(ClientSocket);
    //WSACleanup();
}

void GameServer::start()
{
    SOCKET& socket_server = get_socket();
    

    while (true) {
        Response* response_first = FactoryCommand::create_command(CommandType::FIRST, socket_server);
        std::string* mesaj_client = response_first->execute(); // "op_login"
        cout << "MESAJ CLIENT: " << *mesaj_client << endl;
        CommandType command_type = FactoryCommand::string_command_type(*mesaj_client);
        Response* next_client_command = FactoryCommand::create_command(command_type, socket_server);
        next_client_command->execute();
    }
    
}

void GameServer::register_user()
{
}

void GameServer::login_user()
{
}

void GameServer::start_game_poker()
{
}

void GameServer::start_game_blackjack()
{
}
