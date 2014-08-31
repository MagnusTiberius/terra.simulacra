#include "SocketServer.h"


namespace bbg {

SocketServer::SocketServer(std::wstring domain, int port)
	:Socket(domain,port)
{
	bbg::Socket::Listen();
}


SocketServer::~SocketServer(void)
{
	closesocket(ListenSocket);
	WSACleanup();
}

}