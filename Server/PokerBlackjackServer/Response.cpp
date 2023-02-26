#include "Response.h"


CommandType Response::get_com_type()
{
    return this->comType;
}

Response::Response(SOCKET& socket) : socket(socket)
{
}

string* Response::get_message(SOCKET& socket)
{
    char* recvbuf = new char[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int iResult = recv(socket, recvbuf, recvbuflen, 0);
    if (iResult > 0) {
        // printf("Bytes received: %d\n", iResult);
        recvbuf[iResult] = '\0';
        // cout << "Mesaj primit: " << recvbuf << endl;
    }
   
    string* rezultat = new string(recvbuf);
   
    return rezultat;
}

void Response::send_message(SOCKET& socket, string mesaj)
{
    /*char* recvbuf = new char[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;*/
    int iSendResult = send(socket, mesaj.c_str(), strlen(mesaj.c_str()), 0);
    if (iSendResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(socket);
        WSACleanup();
        return;
    }
    // printf("Bytes sent: %d\n", iSendResult);
}