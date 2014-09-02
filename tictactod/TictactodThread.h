#pragma once

#include "Thread.h"
#include "SocketdHandler.h"


class TictactodThread : public bbg::Thread
{
public:
	TictactodThread(SocketdHandler* socketdHandler);
	~TictactodThread(void);
	static TictactodThread* Create(SOCKET clientSocket);
private:
	SocketdHandler* m_pSocketdHandler;
};

