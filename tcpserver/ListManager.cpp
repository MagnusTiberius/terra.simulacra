#pragma once
#include "TcpServerD.h"
#include "ListManager.h"

ListManager::ListManager() : Thread(this) { }

ListManager::~ListManager() { }

unsigned ListManager::ThreadHandlerProc(void)
{
	requestDataManager = QueueManager<RequestData>::Instance();
	TcpServerD* tcpServerD = TcpServerD::Instance();
	while (true)
	{
		requestDataManager->GrantWriterAccess();
		RequestData* itm = requestDataManager->ReadRequestData();
		requestDataManager->ReleaseWriterAccess();
		if (itm != NULL)
		{
			std::string message = itm->GetMessageData();
			printf("[0x%08lx] Message Pulled: %s\n", GetCurrentThreadId(), message.c_str());
			ThreadPool* threadPool = tcpServerD->GetThreadPool();
			SayHandler* sayHandler = new SayHandler(message);
			threadPool->DispatchThread(sayHandler);
		}
	}
	return 0;
}