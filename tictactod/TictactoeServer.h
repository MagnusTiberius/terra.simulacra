#pragma once
#include "SocketServer.h"

using namespace bbg;

class TictactoeServer:public SocketServer
{
public:
	TictactoeServer(void);
	~TictactoeServer(void);
	void Start(void);
};

