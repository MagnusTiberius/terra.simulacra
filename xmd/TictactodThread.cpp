#include "TictactodThread.h"


TictactodThread::TictactodThread(SocketdHandler* socketdHandler):
	Thread(socketdHandler)
{
	m_pSocketdHandler = socketdHandler;
}


TictactodThread::~TictactodThread(void)
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

TictactodThread* TictactodThread::Create(SOCKET clientSocket)
{
	SocketdHandler* socketdHandler = new SocketdHandler(clientSocket);
	TictactodThread* t = new TictactodThread(socketdHandler);
	return t;
}

