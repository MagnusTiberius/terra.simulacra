#pragma once
#include "SocketServer.h"
#include "TictactodThread.h"
#include "BoardManager.h"

using namespace bbg;

class TictactoeServer:public SocketServer
{
public:
	TictactoeServer(void);
	~TictactoeServer(void);
	void Start(void);
	TictactodThread* ReuseThread(void);
private:
	std::map<std::string, TictactodThread*> m_ThreadList;
};

