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
	SocketManager<RequestData>* sm = SocketManager<RequestData>::Instance();
	RequestData* d;
	d = new RequestData();
	d->SetMessageData("LOGIN test1 ;");
	sm->OutBufferWrite(d);
	printf("Send to Write buffer: %s\n", d->GetMessageData().c_str());

	
	for(int i=0; i<50; i++)
	{
		std::string quote = Util::GetRandomQuote();
		d = new RequestData();
		std::string sstr = "SAY " +  std::to_string(GetCurrentThreadId()) + " \"" + quote + "\" " + " ;\n";
		d->SetMessageData(sstr);
		sm->OutBufferWrite(d);
		printf("Send to Write buffer: %s\n", sstr.c_str());
	}

	SocketThread<bbg::RequestData>* t1 = SocketThread<bbg::RequestData>::Create();

	t1->Wait(INFINITE);
	return 0;
}

