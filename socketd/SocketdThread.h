#pragma once

#include "Thread.h"
#include "SocketdHandler.h"

class SocketdThread : public bbg::Thread
{
public:
	SocketdThread(SocketdHandler* socketdHandler);
	~SocketdThread();
	static SocketdThread* Create(SOCKET clientSocket);
private:
	SocketdHandler* m_pSocketdHandler;
};

