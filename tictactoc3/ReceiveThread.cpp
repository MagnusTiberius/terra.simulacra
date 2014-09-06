#include "ReceiveThread.h"


ReceiveThread::ReceiveThread(ReceiveHandler* receiveHandler):
	Thread(receiveHandler)
{
	m_pReceiveHandler = receiveHandler;
}


ReceiveThread::~ReceiveThread(void)
{
}

ReceiveThread* ReceiveThread::Create()
{
	ReceiveHandler* m_pReceiveHandler = new ReceiveHandler();
	ReceiveThread* t = new ReceiveThread(m_pReceiveHandler);
	return t;
}