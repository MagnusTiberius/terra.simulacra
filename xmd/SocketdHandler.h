#pragma once

#include "ThreadHandler.h"
#include "BoardManager.h"
#include "NetGlobal.h"

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

