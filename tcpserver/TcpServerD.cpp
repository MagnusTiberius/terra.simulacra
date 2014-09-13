#include "TcpServerD.h"


TcpServerD* TcpServerD::_instance = 0;

TcpServerD::TcpServerD() : SocketServer(DEFAULT_DOMAIN, (int)DEFAULT_PORT) { }

TcpServerD::~TcpServerD() { }

TcpServerD* TcpServerD::Instance() {
	if (_instance == 0) 
	{
		_instance = new TcpServerD;
	}
	return _instance;
}

void TcpServerD::Start(void)
{
	m_pListManager = new ListManager();
	while (threadPool.IsRunning())
	{
		printf("Listening...\n");
		SOCKET clientSocket = Accept();
		printf("SOCKET # %d...\n", clientSocket);
		TcpClientHandler* handler = new TcpClientHandler(clientSocket);
		threadPool.DispatchThread((ThreadHandler*)handler);
		auto sz = threadPool.GetThreadListSize();
		printf("TCP Server Worker Count: %d\n", sz);
	}
}

ThreadPool* TcpServerD::GetThreadPool()
{
	return &threadPool;
}