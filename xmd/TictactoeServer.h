#pragma once
#include "SocketServer.h"
#include "TictactodThread.h"
#include "BoardManager.h"
#include "ClientManager.h"
#include "ClientXm.h"

using namespace bbg;

class TictactoeServer:public SocketServer
{
public:
	TictactoeServer(void);
	~TictactoeServer(void);
	void Start(void);
};

