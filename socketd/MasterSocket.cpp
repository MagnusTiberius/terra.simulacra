#include "stdafx.h"
#include "MasterSocket.h"


MasterSocket::MasterSocket(void)
	:SocketServer(DEFAULT_DOMAIN, (int)DEFAULT_PORT)
{
}


MasterSocket::~MasterSocket(void)
{
}

void MasterSocket::Start(void)
{
	do {
		printf("Listening...\n");
		SOCKET clientSocket = Accept();
		SocketdThread* socketdThread = SocketdThread::Create(clientSocket);
		auto w = socketdThread->Wait(100);
		delete socketdThread;
	} while (true);
}