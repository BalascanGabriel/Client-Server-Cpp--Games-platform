#include "Com.h"

Com::Com()
{
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    // getaddrinfo()
    iResult = getaddrinfo("localhost", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return ;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return ;
    }
}


std::string Com::get_message()
{
    char* recvbuf = new char[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    if (iResult > 0) {
        // printf("Bytes received: %d\n", iResult);
        recvbuf[iResult] = '\0';
        // cout << "Mesaj primit: " << recvbuf << endl;
    }
    std::string rezultat = std::string(recvbuf);
    return rezultat;
}

void Com::send_message(std::string mesaj)
{
    /*char* recvbuf = new char[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;*/
    int iSendResult = send(ConnectSocket, mesaj.c_str(), strlen(mesaj.c_str()), 0);
    if (iSendResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return;
    }
    // printf("Bytes sent: %d\n", iSendResult);
}