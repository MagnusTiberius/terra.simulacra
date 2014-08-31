#pragma once
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include "SocketdThread.h"

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

class SocketServer
{
public:
	SocketServer(void);
	~SocketServer(void);
	void Start(void);
private:
	SOCKET ListenSocket;
	SOCKET ClientSocket;
	WSADATA wsaData;
	int iResult;
	int iSendResult;
	int recvbuflen;
	char recvbuf[DEFAULT_BUFLEN];
	struct addrinfo *result;
	struct addrinfo hints;
};

