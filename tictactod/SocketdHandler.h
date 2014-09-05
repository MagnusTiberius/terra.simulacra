#pragma once

#include "ThreadHandler.h"
#include "BoardManager.h"
#include "NetGlobal.h"
#include "RequestDataManager.h"
#include "RequestData.h"
#include "Util.h"

class SocketdHandler : public bbg::ThreadHandler
{
public:
	SocketdHandler(SOCKET clientSocket);
	
	~SocketdHandler();
	virtual unsigned ThreadHandlerProc(void);
	BOOL isHandlerDone();
	void SetSocket(SOCKET socket);
	SOCKET GetSocket();
	void SetDone(BOOL bValue);
private:
	SOCKET m_clientSocket;
	BOOL isDone;
	RequestDataManager* requestDataManager;
};

