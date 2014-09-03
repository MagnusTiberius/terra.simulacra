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
	auto ref = BoardManager::Instance();
	ref->Init();
	do {
		printf("Listening...\n");
		SOCKET clientSocket = Accept();
		ClientXm* c = new ClientXm(clientSocket);
		ClientManager* m = ClientManager::Instance();
		m->AddClient(new ClientXm(clientSocket));
	} while (true);
}