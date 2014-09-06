#include "BroadcastThread.h"

namespace bbg {

BroadcastThread::BroadcastThread(bbg::BroadcastHandler* handler)
	:bbg::Thread(handler)
{
	m_pHandler = handler;
}


BroadcastThread::~BroadcastThread(void)
{
}

BroadcastThread* BroadcastThread::Create()
{
	bbg::BroadcastHandler* m_pSocketdHandler = new bbg::BroadcastHandler();
	BroadcastThread* t = new BroadcastThread(m_pSocketdHandler);
	return t;
}

}
