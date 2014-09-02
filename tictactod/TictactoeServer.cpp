#include "TictactoeServer.h"


TictactoeServer::TictactoeServer(void)
	:SocketServer(DEFAULT_DOMAIN, (int)DEFAULT_PORT)
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
		TictactodThread* t = TictactodThread::Create(clientSocket);
		auto w = t->Wait(100);
		delete t;
	} while (true);
}