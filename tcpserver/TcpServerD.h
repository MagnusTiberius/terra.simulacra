#pragma once
#include "stdafx.h"
#include "SocketServer.h"
#include "BoardManager.h"
#include "ThreadPool.h"
#include "TaskThreadHandler.h"
#include "ThreadHandler.h"
#include "ListManager.h"
#include "TcpClientHandler.h"

class TcpServerD:public SocketServer
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
	static TcpServerD* _instance;
};


