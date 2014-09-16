#include "TcpServerD.h"

namespace bbg {

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
	m_pCommandManager = CommandManager::Instance();
	m_pListManager = new ListManager();
	while (threadPool.IsRunning())
	{
		printf("[0x%08lx] TcpServerD::Start() Listening \n", GetCurrentThreadId());
		SOCKET clientSocket = Accept();
		printf("SOCKET # %d...\n", clientSocket);
		TcpClientHandler* handler = new TcpClientHandler(clientSocket);
		threadPool.DispatchThread((ThreadHandler*)handler);
	}
}

ThreadPool* TcpServerD::GetThreadPool()
{
	return &threadPool;
}

}