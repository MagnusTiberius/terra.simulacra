#include "TictactoeServer.h"


TictactoeServer::TictactoeServer(void)
{
}


TictactoeServer::~TictactoeServer(void)
{
}

void TictactoeServer::Start(void)
{
	do {
		printf("Listening...\n");
		SOCKET clientSocket = Accept();
		SocketdThread* socketdThread = SocketdThread::Create(clientSocket);
		auto w = socketdThread->Wait(100);
		delete socketdThread;
	} while (true);
}