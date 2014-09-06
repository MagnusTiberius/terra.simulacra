#pragma once

#include "Socket.h"

using namespace bbg;

class ClientSocket : public Socket
{
public:
	ClientSocket(void);
	ClientSocket(SOCKET socket);
	ClientSocket(std::wstring domain, int port);
	~ClientSocket(void);
};

