#pragma once

#include "ThreadHandler.h"
#include "BoardManager.h"


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

class SocketdHandler : public bbg::ThreadHandler
{
public:
	SocketdHandler(SOCKET clientSocket);
	~SocketdHandler();
	virtual unsigned ThreadHandlerProc(void);
private:
	SOCKET m_clientSocket;
	BOOL isDone;
};

