// tcpserver.cpp : Defines the entry point for the console application.
//

#pragma once
#include "stdafx.h"
#include "SocketServer.h"
#include "BoardManager.h"
#include "ThreadPool.h"
#include "TaskThreadHandler.h"
#include "ThreadHandler.h"
#include "TcpClientHandler.h"
#include "TcpServerD.h"




int _tmain(int argc, _TCHAR* argv[])
{
	TcpServerD* tcpServerD = TcpServerD::Instance();
	tcpServerD->Start();
	return 0;
}

