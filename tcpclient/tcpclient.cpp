// tcpclient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "RequestData.h"
#include "SocketThread.h"
#include "SocketManager.h"
#include "Util.h"

#include "Thread.h"
#include "ThreadHandler.h"


using namespace bbg;

template <class T>
class ClientManager : public Thread, ThreadHandler
{
public:
	ClientManager(void);
	~ClientManager(void);
	virtual unsigned ThreadHandlerProc(void);
	static ClientManager* Instance();
	bool IsConnected(void);
private:
	static ClientManager* m_Instance;
	bbg::SocketClient* socketClient;
	bool m_bIsConnected;
};

template <class T>
ClientManager<T>* ClientManager<T>::m_Instance = 0;

template <class T>
ClientManager<T>* ClientManager<T>::Instance() {
	if (m_Instance == 0) {
		m_Instance = new ClientManager<T>();
	}
	return m_Instance;
}

template <class T>
ClientManager<T>::ClientManager(void) : Thread(this), ThreadHandler()
{
	Suspend();
	socketClient = new bbg::SocketClient(DEFAULT_DOMAIN, (int)DEFAULT_PORT);
	Resume();
	m_bIsConnected = true;
}

template <class T>
ClientManager<T>::~ClientManager(void)
{
}

template <class T>
bool ClientManager<T>::IsConnected(void)
{
	return m_bIsConnected;
}

template <class T>
unsigned ClientManager<T>::ThreadHandlerProc(void)
{
	SocketManager<RequestData>* socketManager = SocketManager<RequestData>::Instance();
	int nCtr = 0;
	bool inLoop = true;
	char* buf;
	int iResult;
	m_bIsConnected = true;
	while (inLoop)
	{
		printf("[0x%08lx] ClientManager ThreadHandlerProc : \n", GetCurrentThreadId());
		RequestData* requestData = new RequestData();
		requestData->SetMessageData("#*#");
		requestData = socketManager->OutBufferRead();
		if (requestData != NULL)
		{
			if (requestData->GetMessageData().compare("#*#") != 0)
			{
				printf("Sending to server: %s %d\n", requestData->GetMessageData().c_str(), nCtr++);
				buf = const_cast<char*>(requestData->GetMessageData().c_str());
				char* b = const_cast<char*>(requestData->GetMessageData().c_str());
				std::string sMessageData = requestData->GetMessageData();
				const char* pSendData = sMessageData.c_str();
				iResult = socketClient->Send(const_cast<char*>(pSendData));
				if (iResult == -1 || iResult == 0)
				{
					inLoop = false;
					m_bIsConnected = false;
				}
			}
			if (requestData->GetMessageData().compare("QUIT") == 0 || requestData->GetMessageData().compare("QUIT ") == 0)
				inLoop = false;
		}
	}
	return 0;
}

// =====================================================================================
//
//
// =====================================================================================

int _tmain(int argc, _TCHAR* argv[])
{
	SocketManager<RequestData>* socketManager = SocketManager<RequestData>::Instance();
	ClientManager<RequestData>* socketThread = ClientManager<RequestData>::Instance();
	RequestData* requestData;
	requestData = new RequestData();
	if (socketThread->IsConnected())
	{
		requestData->SetMessageData("LOGIN test1 ;");
		socketManager->OutBufferWrite(requestData);
		printf("Send to Write buffer: %s\n", requestData->GetMessageData().c_str());
	}
	for (int i = 0; i<100000; i++)
	{
		if (socketThread->IsConnected())
		{
			::Sleep(50);
			std::string randomQuote = Util::GetRandomQuote();
			requestData = new RequestData();
			std::string sRandomQuote = "SAY " + std::to_string(GetCurrentThreadId()) + " \"" + randomQuote + "\" " + " ;\n";
			requestData->SetMessageData(sRandomQuote);
			socketManager->OutBufferWrite(requestData);
			printf("Sending to Write buffer: %s\n", sRandomQuote.c_str());
		}
	}
	if (socketThread->IsConnected())
	{
		std::string sQuit = "QUIT ";
		requestData->SetMessageData(sQuit);
		socketManager->OutBufferWrite(requestData);
		socketThread->Wait(INFINITE);
	}
	::Sleep(1000);
	return 0;
}

