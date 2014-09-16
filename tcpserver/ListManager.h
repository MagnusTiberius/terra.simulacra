#pragma once
#include "Thread.h"
#include "ThreadHandler.h"
#include "Queuemanager.h"
#include "RequestData.h"
#include "CommandManager.h"
#include "Command.h"
#include "CommandAnalyticsClient.h"

namespace bbg {

using namespace bbg;

class SayHandler :public ThreadHandler
{
public:
	SayHandler(void) {}
	SayHandler(std::string msg) 
	{
		m_msg = msg;
	}
	~SayHandler(void) {}
	virtual unsigned ThreadHandlerProc(void)
	{
		printf("[0x%08lx] Inside SayHandler: %s\n", GetCurrentThreadId() , m_msg.c_str());
		return 0;
	}
private:
	std::string m_msg;
};

class IasHandler :public ThreadHandler
{
public:
	IasHandler(void) {}
	IasHandler(std::string msg)
	{
		m_msg = msg;
	}
	~IasHandler(void) {}
	virtual unsigned ThreadHandlerProc(void)
	{
		printf("[0x%08lx] Inside IasHandler: %s\n", GetCurrentThreadId(), m_msg.c_str());
		return 0;
	}
private:
	std::string m_msg;
};


class ListManager : public Thread, ThreadHandler
{
public:
	ListManager();
	~ListManager();
	virtual unsigned ThreadHandlerProc(void);
private:
	QueueManager<RequestData>* requestDataManager;
};

}