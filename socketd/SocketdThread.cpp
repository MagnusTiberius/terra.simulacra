#include "SocketdThread.h"


SocketdThread::SocketdThread(SocketdHandler* socketdHandler) :
	Thread(socketdHandler)
{
	m_pSocketdHandler = socketdHandler;
}


SocketdThread::~SocketdThread()
{
	auto w = Wait(INFINITE);
	if (bbg::WaitSucceeded(w, 0) || bbg::WaitAbandoned(w, 0))
	{
		if (m_pSocketdHandler)
			delete m_pSocketdHandler;
	}
	else
	{
		if (m_pSocketdHandler)
			delete m_pSocketdHandler;
	}

}

SocketdThread* SocketdThread::Create(SOCKET clientSocket)
{
	SocketdHandler* socketdHandler = new SocketdHandler(clientSocket);
	SocketdThread* socketdThread = new SocketdThread(socketdHandler);
	return socketdThread;
}