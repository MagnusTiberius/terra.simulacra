#include "ClientSocketHandler.h"


ClientSocketHandler::ClientSocketHandler(void)
{
}


ClientSocketHandler::~ClientSocketHandler(void)
{
}

unsigned ClientSocketHandler::ThreadHandlerProc(void)
{
	return 0;
}

void ClientSocketHandler::SetSocket(SOCKET s)
{
	m_s = s;
	m_Socket = new Socket(s);
}