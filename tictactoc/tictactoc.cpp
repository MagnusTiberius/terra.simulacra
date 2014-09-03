// tictactoc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ClientSocket.h"
#include "User.h"


int _tmain(int argc, _TCHAR* argv[])
{
	char* buffer = "SHOW List ;";
	char* receiveBuffer = (char*)malloc(512);
	User user;

	ClientSocket client(DEFAULT_DOMAIN, (int)DEFAULT_PORT);

	for (int n=1; n<5; n++)
	{
		std::string s ;
		char* buf;
		int iResult;

		if (n == 1)
		{
			s = "LOGIN " + user.GetLoginId() + " ;";
			buf = const_cast<char*>(s.c_str());
			iResult = client.Send(buf);
			if (iResult == SOCKET_ERROR) 
			{
				printf("send failed with error: %d\n", WSAGetLastError());
				exit(1);
			}
			printf("Bytes Sent: %ld\n", iResult);
		}
		if (n == 2)
		{
			string q = Util::GetRandomQuote();
			s = "SAY " + user.GetLoginId() + " \"" + q + "\" ;";
			buf = const_cast<char*>(s.c_str());
			iResult = client.Send(buf);
			printf("Bytes Sent: %ld\n", iResult);
		}
		if (n == 3)
		{
			s = "QUIT ";
			buf = const_cast<char*>(s.c_str());
			iResult = client.Send(buf);
			printf("Bytes Sent: %ld\n", iResult);
		}
		if (n == 4)
		{
			iResult = client.Shutdown();
			printf("Bytes Sent: %ld\n", iResult);
		}

		iResult = client.Receive(receiveBuffer, 512);
		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());
	}
	return 0;
}

