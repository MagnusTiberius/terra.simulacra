#pragma once
#include "ReceiveHandler.h"
#include "Thread.h"

class ReceiveThread: public bbg::Thread
{
public:
	ReceiveThread(ReceiveHandler* receiveHandler);
	~ReceiveThread(void);
	static ReceiveThread* Create();

private:
	ReceiveHandler* m_pReceiveHandler;
};

