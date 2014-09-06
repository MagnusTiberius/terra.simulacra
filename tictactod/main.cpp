// tictactod.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TictactoeServer.h"
#include "RequestDataManager.h"
#include "BroadcastThread.h"

int _tmain(int argc, _TCHAR* argv[])
{
	BroadcastThread* b1 = BroadcastThread::Create();
	BroadcastThread* b2 = BroadcastThread::Create();
	BroadcastThread* b3 = BroadcastThread::Create();
	std::cout << "Thread Created [" << b1->GetThreadId() << "]  " << b1->GetHandle() << "\n";
	std::cout << "Thread Created [" << b2->GetThreadId() << "]  " << b2->GetHandle() << "\n";
	std::cout << "Thread Created [" << b3->GetThreadId() << "]  " << b3->GetHandle() << "\n";
	RequestDataManager<RequestData>* requestDataManager = RequestDataManager<RequestData>::Instance();
	requestDataManager->SetBufferSize(1024*5);
	TictactoeServer server;
	server.Start();
	b1->Wait(INFINITE);
	b2->Wait(INFINITE);
	b3->Wait(INFINITE);
	return 0;
}

