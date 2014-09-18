#pragma once
#include "stdafx.h"
#include "SocketServer.h"
#include "BoardManager.h"
#include "ThreadPool.h"
#include "TaskThreadHandler.h"
#include "ThreadHandler.h"
#include "ListManager.h"
#include "TcpClientHandler.h"
#include "CommandManager.h"
#include "ConnectionManager.h"
#include "ChannelManager.h"
#include <map>
#include <string>
#include "Stage.h"

namespace bbg {

using namespace bbg;


class TcpServerD :public SocketServer
{
public:
	TcpServerD();
	~TcpServerD();
	void Start(void);
	static TcpServerD* Instance();
	ThreadPool* GetThreadPool();
private:
	ThreadPool threadPool;
	ListManager* m_pListManager;
	CommandManager* m_pCommandManager;
	static TcpServerD* _instance;
	ConnectionManager* connectionList;
};

}