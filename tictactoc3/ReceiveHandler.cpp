#include "ReceiveHandler.h"


ReceiveHandler::ReceiveHandler(void):
	ThreadHandler()
{

}

ReceiveHandler::~ReceiveHandler(void)
{
}


unsigned ReceiveHandler::ThreadHandlerProc(void)
{
	char* buffer = "LISTEN ON;";
	char* receiveBuffer = (char*)malloc(512);
	ClientSocket client(DEFAULT_DOMAIN, (int)DEFAULT_PORT);
	auto iResult1 = client.Send(buffer);

	while (true)
	{
		//printf("Sending message...\n");
		//auto iResult = client.Send(buffer);
		auto iResult = client.Receive(receiveBuffer, 512);
		if (iResult != SOCKET_ERROR) 
		{
			printf("Bytes Receive: %ld\n", iResult);
			char* sbuf = (char*)malloc(sizeof(char)*iResult);
			memset(sbuf,0,iResult);
			memcpy(sbuf,&receiveBuffer[0],iResult);
			printf("Content 2: %s\n", sbuf);
		}

	}
	return 0;
}