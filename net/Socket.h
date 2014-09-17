#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include "Url.h"
#include "NetGlobal.h"

namespace bbg {

class Socket
{
public:
	Socket(void);
	Socket(std::wstring domain, int port);
	Socket(SOCKET socket);
	~Socket(void);
	int Send(char* buffer);
	int Shutdown();
	int Receive(char* recvbuf, int recvbuflen);
	int ConnectToServer();
	int Listen();
	SOCKET GetClientSocket();
	SOCKET Accept(void);
	bool IsPortAvailable(std::wstring domain, int port);
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
protected:
	int m_currentPort;
};

}