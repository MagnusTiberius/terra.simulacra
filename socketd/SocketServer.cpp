#include "stdafx.h"
#include "SocketServer.h"


SocketServer::SocketServer(void)
{
	ListenSocket = INVALID_SOCKET;
	ClientSocket = INVALID_SOCKET;
	recvbuflen = DEFAULT_BUFLEN;
}

void SocketServer::Start(void)
{
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
		return;
	}

	//SetConsoleCtrlHandler(HandlerRoutine, TRUE);

	// Accept a client socket
	do
	{
		printf("listening...\n");
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return;
		}
		printf("ClientSocket...%d\n", ClientSocket); 
		SocketdThread* socketdThread = SocketdThread::Create(ClientSocket);
		auto w = socketdThread->Wait(100);
		//auto t = socketdThread->Terminate(1);
		delete socketdThread;
	} while (true);


}


SocketServer::~SocketServer(void)
{
	printf("ClientSocket returned\n");
	// No longer need server socket
	closesocket(ListenSocket);
	closesocket(ClientSocket);
	WSACleanup();
}
