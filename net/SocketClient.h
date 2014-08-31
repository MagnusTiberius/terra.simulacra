#pragma once

#include "Socket.h"


class SocketClient : public bbg::Socket
{
public:
	SocketClient(std::wstring domain, int port);
	~SocketClient(void);
};

