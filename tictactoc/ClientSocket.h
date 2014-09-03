#pragma once

#include "Socket.h"

using namespace bbg;

class ClientSocket : public Socket
{
public:
	ClientSocket(std::wstring domain, int port);
	~ClientSocket(void);
};

