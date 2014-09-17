#pragma once

#include "Thread.h"
#include "ThreadHandler.h"

using namespace bbg;

class ChannelManager : public Thread, ThreadHandler
{
public:
	ChannelManager();
	~ChannelManager();
	virtual unsigned ThreadHandlerProc(void);
	static ChannelManager* Instance();
private:
	static ChannelManager* m_Instance;
};

