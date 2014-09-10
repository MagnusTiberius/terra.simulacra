#pragma once
#include "Socket.h"
#include "ThreadHandler.h"

using namespace  bbg;

class ClientSocketHandler: public ThreadHandler
{
public:
	ClientSocketHandler(void);
	~ClientSocketHandler(void);
	virtual unsigned ThreadHandlerProc(void);
	void SetSocket(SOCKET socket);
private:
	SOCKET m_s;
	Socket* m_Socket;
};

