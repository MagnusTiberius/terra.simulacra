#pragma once

#include "ThreadHandler.h"
#include "RequestDataManager.h"
#include <thread>
#include "Util.h"
#include <iostream>

namespace bbg {

class BroadcastHandler : public bbg::ThreadHandler
{
public:
	BroadcastHandler(void);
	~BroadcastHandler(void);
	virtual unsigned ThreadHandlerProc(void);
protected:
	RequestDataManager<RequestData>* handler;
	std::thread::id m_tid;
	char* name;
};

}