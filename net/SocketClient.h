#pragma once

#include "Socket.h"

namespace bbg {

class SocketClient : public bbg::Socket
{
public:
	SocketClient(std::wstring domain, int port);
	~SocketClient(void);
};

}