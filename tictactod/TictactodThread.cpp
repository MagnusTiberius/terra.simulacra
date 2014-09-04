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
		Terminate(1);
		if (m_pSocketdHandler)
			delete m_pSocketdHandler;
	}
	else
	{
		Terminate(1);
		if (m_pSocketdHandler)
			delete m_pSocketdHandler;
	}
	printf("Thread handler deleted...\n");
	printf("~TictactodThread()\n");
}

void TictactodThread::SetSocket(SOCKET clientSocket)
{
	m_pSocketdHandler->SetSocket(clientSocket);
	SetHandler(m_pSocketdHandler);
}

TictactodThread* TictactodThread::Create(SOCKET clientSocket)
{
	SocketdHandler* m_pSocketdHandler = new SocketdHandler(clientSocket);
	TictactodThread* t = new TictactodThread(m_pSocketdHandler);
	return t;
}

BOOL TictactodThread::isHandlerDone()
{
	return m_pSocketdHandler->isHandlerDone();
}

BOOL TictactodThread::isSocketOpen()
{
	SOCKET socket = m_pSocketdHandler->GetSocket();
	char* buf = " ";
	int nResult = recv(socket, buf, 1, MSG_PEEK);
	if (nResult == SOCKET_ERROR)
	{
		//Terminate(1);
		//m_pSocketdHandler->SetDone(true);
		return false;
	}
	return true;
}