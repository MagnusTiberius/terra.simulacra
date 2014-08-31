// socketd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "server.h"
//#include "SocketServer.h"
#include "MasterSocket.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//server_main();
	MasterSocket socketServer;
	socketServer.Start();
	return 0;
}

