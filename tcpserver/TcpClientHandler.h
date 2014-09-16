#pragma once
#include "stdafx.h"
#include "SocketServer.h"
#include "BoardManager.h"
#include "ThreadPool.h"
#include "TaskThreadHandler.h"
#include "ThreadHandler.h"
#include "QueueManager.h"
//#include "iaslib.h"
#include "CommandManager.h"
#include "Command.h"

namespace bbg {

using namespace bbg;

class TcpClientHandler :ThreadHandler
{
public:
	TcpClientHandler();
	TcpClientHandler(SOCKET socket);
	~TcpClientHandler();
	virtual unsigned ThreadHandlerProc(void);
private:
	SOCKET m_socket;
	BOOL isDone;
	QueueManager<RequestData>* requestDataManager;
};

}