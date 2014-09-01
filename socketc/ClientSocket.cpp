#include "stdafx.h"
#include "ClientSocket.h"


ClientSocket::ClientSocket(std::wstring domain, int port)
	:Socket(domain, port)
{
	ConnectToServer();
}


ClientSocket::~ClientSocket(void)
{
}
