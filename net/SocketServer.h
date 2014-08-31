#pragma once
#include "Socket.h"

namespace bbg {

class SocketServer: public bbg::Socket
{
public:
	SocketServer(std::wstring domain, int port);
	~SocketServer(void);
private:
	bbg::Socket m_socket;
};

}