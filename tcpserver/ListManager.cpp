#pragma once
#include "TcpServerD.h"
#include "ListManager.h"



ListManager::ListManager() : Thread(this) { }

ListManager::~ListManager() { }

unsigned ListManager::ThreadHandlerProc(void)
{
	CommandManager* commandManager = CommandManager::Instance();
	requestDataManager = QueueManager<RequestData>::Instance();
	TcpServerD* tcpServerD = TcpServerD::Instance();
	long loopCtr = 0;
	while (true)
	{
		printf("[0x%08lx] Message Pulled Ctr: %d\n", GetCurrentThreadId(), loopCtr++);
		requestDataManager->GrantReaderAccessEx();
		RequestData* itm = requestDataManager->ReadRequestData();
		requestDataManager->ReleaseReaderAccessEx();
		if (itm != NULL)
		{
			std::string message = itm->GetMessageData();
			printf("[0x%08lx] Message Pulled: %s\n", GetCurrentThreadId(), message.c_str());
			ThreadPool* threadPool = tcpServerD->GetThreadPool();
			SayHandler* sayHandler = new SayHandler(message);
			threadPool->DispatchThread(sayHandler);
			//
			CommandAnalyticsClient* command = new CommandAnalyticsClient();
			auto commandList = commandManager->GetCommandList();
			if (commandList != NULL)
			{
				commandList->GrantWriterAccessEx();
				commandList->AddRequestData(command);
				commandList->ReleaseWriterAccessEx();
			}
		}
	}
	return 0;
}