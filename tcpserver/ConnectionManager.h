#pragma once
#include "SocketServer.h"
#include "BoardManager.h"
#include "ThreadPool.h"
#include "TaskThreadHandler.h"
#include "ThreadHandler.h"
#include "ListManager.h"
#include "TcpClientHandler.h"
#include "CommandManager.h"
#include <map>
#include <string>

class ConnectedSocketInfo
{
public:
	ConnectedSocketInfo(void) {}
	~ConnectedSocketInfo(void) {}
	ConnectedSocketInfo(int socket, TcpClientHandler* handler)
		:m_iSocket(socket), m_pHandler(handler), m_iLocation(0)
	{
	}
private:
	int m_iSocket;
	TcpClientHandler* m_pHandler;
	int m_iLocation;
};


class ConnectionManager
{
public:
	ConnectionManager(void);
	~ConnectionManager(void);
	void Add(int n, ConnectedSocketInfo* p);
public:
	static ConnectionManager* Instance();
private:
	std::map<int, ConnectedSocketInfo*> m_ConnectionListManager;
	static ConnectionManager* m_Instance;
};



