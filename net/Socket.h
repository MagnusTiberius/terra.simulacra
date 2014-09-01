#pragma once


#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include "Url.h"

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define DEFAULT_DOMAIN L"127.0.0.1"

namespace bbg {

class Socket
{
public:
	Socket(void);
	Socket(std::wstring domain, int port);
	~Socket(void);
	int Send(char* buffer);
	int Shutdown();
	int Receive(char* recvbuf, int recvbuflen);
	int ConnectToServer();
	int Listen();
	SOCKET Accept(void);
protected:
	SOCKET ListenSocket;
	SOCKET ClientSocket;
	SOCKET ConnectSocket;
	WSADATA wsaData;
	int iResult;
	int iSendResult;
	int recvbuflen;
	char recvbuf[DEFAULT_BUFLEN];
	struct addrinfo *result;
	struct addrinfo hints;
	struct addrinfo *ptr;
};

}