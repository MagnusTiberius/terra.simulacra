#pragma once

#include "../net/SocketServer.h"
#include "SocketdThread.h"

class MasterSocket :public bbg::SocketServer
{
public:
	MasterSocket(void);
	~MasterSocket(void);
	void Start(void);
};

