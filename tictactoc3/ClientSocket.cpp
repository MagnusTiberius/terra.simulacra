#include "ClientSocket.h"


ClientSocket::ClientSocket()
{

}

ClientSocket::ClientSocket(std::wstring domain, int port)
	:Socket(domain, port)
{
	ConnectToServer();
}

ClientSocket::ClientSocket(SOCKET socket)
	:Socket(socket)
{

}

ClientSocket::~ClientSocket(void)
{
}
