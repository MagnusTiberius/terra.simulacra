#pragma once
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include "server.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#include "NetGlobal.h"

volatile bool isRunnung = true;

BOOL WINAPI HandlerRoutine(_In_ DWORD dwCtrlType);


int __cdecl server_main(void)
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
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
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
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
			return 1;
		}
		printf("ClientSocket...%d\n", ClientSocket); 
		SocketdThread* socketdThread = SocketdThread::Create(ClientSocket);
		auto w = socketdThread->Wait(100);
		//auto t = socketdThread->Terminate(1);
		delete socketdThread;
	} while (true);

	printf("ClientSocket returned\n");
	// No longer need server socket
	closesocket(ListenSocket);

	// Receive until the peer shuts down the connection
	//do {

	//	iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
	//	if (iResult > 0) {
	//		printf("Bytes received: %d\n", iResult);

	//		// Echo the buffer back to the sender
	//		iSendResult = send(ClientSocket, recvbuf, iResult, 0);
	//		if (iSendResult == SOCKET_ERROR) {
	//			printf("send failed with error: %d\n", WSAGetLastError());
	//			closesocket(ClientSocket);
	//			WSACleanup();
	//			return 1;
	//		}
	//		printf("Bytes sent: %d\n", iSendResult);
	//	}
	//	else if (iResult == 0)
	//		printf("Connection closing...\n");
	//	else  {
	//		printf("recv failed with error: %d\n", WSAGetLastError());
	//		closesocket(ClientSocket);
	//		WSACleanup();
	//		return 1;
	//	}

	//} while (iResult > 0 && isRunnung);

	// shutdown the connection since we're done
	//iResult = shutdown(ClientSocket, SD_SEND);
	//if (iResult == SOCKET_ERROR) {
	//	printf("shutdown failed with error: %d\n", WSAGetLastError());
	//	closesocket(ClientSocket);
	//	WSACleanup();
	//	return 1;
	//}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}


BOOL WINAPI HandlerRoutine(_In_ DWORD dwCtrlType) 
{
	switch (dwCtrlType)
	{
	case CTRL_C_EVENT:
		printf("[Ctrl]+C\n");
		isRunnung = false;
		// Signal is handled - don't pass it on to the next handler
		return TRUE;
	default:
		// Pass signal on to the next handler
		return FALSE;
	}
}