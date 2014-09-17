// tictactoc3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "RequestData.h"
#include "SocketThread.h"
#include "SocketManager.h"
#include "Util.h"

using namespace bbg;

int _tmain(int argc, _TCHAR* argv[])
{
	SocketManager<RequestData>* socketManager = SocketManager<RequestData>::Instance();
	RequestData* requestData;
	requestData = new RequestData();
	requestData->SetMessageData("LOGIN test1 ;");
	socketManager->OutBufferWrite(requestData);
	printf("Send to Write buffer: %s\n", requestData->GetMessageData().c_str());
	SocketThread<RequestData>* socketThread = SocketThread<RequestData>::Create();
	for(int i=0; i<1000000; i++)
	{
		::Sleep(50);
		std::string randomQuote = Util::GetRandomQuote();
		requestData = new RequestData();
		std::string sRandomQuote = "SAY " + std::to_string(GetCurrentThreadId()) + " \"" + randomQuote + "\" " + " ;\n";
		requestData->SetMessageData(sRandomQuote);
		socketManager->OutBufferWrite(requestData);
		printf("Sending to Write buffer: %s\n", sRandomQuote.c_str());
	}
	std::string sQuit = "QUIT ";
	requestData->SetMessageData(sQuit);
	socketManager->OutBufferWrite(requestData);
	socketThread->Wait(INFINITE);
	return 0;
}

