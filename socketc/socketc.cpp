#pragma once

#include "stdafx.h"
#include "ClientSocket.h"


int _tmain(int argc, _TCHAR* argv[])
{
	char* buffer = "This is a test";
	char* receiveBuffer = (char*)malloc(512);

	ClientSocket client(DEFAULT_DOMAIN, (int)DEFAULT_PORT);
	auto iResult = client.Send(buffer);
	if (iResult == SOCKET_ERROR) 
	{
		printf("send failed with error: %d\n", WSAGetLastError());
		exit(1);
	}
	printf("Bytes Sent: %ld\n", iResult);

	iResult = client.Shutdown();
	do {

		iResult = client.Receive(receiveBuffer, 512);
		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());

	} while (iResult > 0);
	return 0;
}

