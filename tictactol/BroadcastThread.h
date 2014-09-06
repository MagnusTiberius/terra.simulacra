#pragma once
#include "BroadcastHandler.h"
#include "Thread.h"

namespace bbg {

class BroadcastThread : public bbg::Thread
{
public:
	BroadcastThread(bbg::BroadcastHandler* handler);
	~BroadcastThread(void);
	static BroadcastThread* Create();
private:
	bbg::BroadcastHandler* m_pHandler;
};

}