// tictactoc3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ClientSocket.h"
#include "ReceiveThread.h"
#include "stdio.h"
#include "stdlib.h"
#include "BroadcastThread.h"


int _tmain(int argc, _TCHAR* argv[])
{
	char* buffer = "This is a test";
	char* receiveBuffer = (char*)malloc(512);

	printf("Listening on receive...\n");
	//ClientSocket client(DEFAULT_DOMAIN, (int)DEFAULT_PORT);
	//auto iResult = client.Send(buffer);
	
	ReceiveThread* t = ReceiveThread::Create();
	t->Wait(INFINITE);
	
	return 0;
}

