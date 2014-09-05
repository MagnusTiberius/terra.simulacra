// tictactoc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ClientSocket.h"
#include "User.h"
#include <chrono>
#include <thread>

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
		printf("Count: %ld\n", n);
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
			for(int k=0; k<20; k++)
			{
				printf("Quite Count: %ld\n", k);
				string q = Util::GetRandomQuote();
				s = "SAY " + user.GetLoginId() + "-" + std::to_string(k+1) + " \"" + q + "\" ;";
				buf = const_cast<char*>(s.c_str());
				iResult = client.Send(buf);
				if (iResult == SOCKET_ERROR) 
				{
					printf("send failed with error: %d\n", WSAGetLastError());
					exit(1);
				}
				printf("Bytes Sent: %ld\n", iResult);
				std::chrono::milliseconds dura( 10 );
				std::this_thread::sleep_for( dura );
			}
		}
		if (n == 3)
		{
			s = "QUIT ;";
			buf = const_cast<char*>(s.c_str());
			iResult = client.Send(buf);
			if (iResult == SOCKET_ERROR) 
			{
				printf("send failed with error: %d\n", WSAGetLastError());
				exit(1);
			}
			printf("Bytes Sent: %ld\n", iResult);
		}
		if (n == 4)
		{
			iResult = client.Shutdown();
			if (iResult == SOCKET_ERROR) 
			{
				printf("send failed with error: %d\n", WSAGetLastError());
				exit(1);
			}
			printf("Bytes Sent: %ld\n", iResult);
		}

		//iResult = client.Receive(receiveBuffer, 512);
		//if (iResult > 0)
		//	printf("Bytes received: %d\n", iResult);
		//else if (iResult == 0)
		//	printf("Connection closed\n");
		//else
		//	printf("recv failed with error: %d\n", WSAGetLastError());
	}
	std::chrono::milliseconds dura( 500 );
	std::this_thread::sleep_for( dura );
	return 0;
}

