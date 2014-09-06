#pragma once
#include "ClientSocket.h"
#include "ThreadHandler.h"
#include "stdio.h"
#include "stdlib.h"

class ReceiveHandler: public bbg::ThreadHandler
{
public:
	ReceiveHandler(void);
	~ReceiveHandler(void);
	virtual unsigned ThreadHandlerProc(void);
private:
	ClientSocket* m_clientSocket;
};

