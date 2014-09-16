#pragma once
#include "QueueManager.h"
#include "Command.h"
#include "Thread.h"
#include "ThreadHandler.h"

namespace bbg {

using namespace bbg;

class CommandWorker : public ThreadHandler, Thread
{
public:
	CommandWorker() : Thread(this) {}
	virtual unsigned ThreadHandlerProc(void)
	{
		while (true)
		{
			QueueManager<Command>* m_CommandList = QueueManager<Command>::Instance();
			m_CommandList->GrantReaderAccessEx();
			Command* command = m_CommandList->ReadRequestData();
			m_CommandList->ReleaseReaderAccessEx();
			if (command != NULL)
			{
				printf("[0x%08lx] >>> CommandManager ThreadHandlerProc: Executing command start \n", GetCurrentThreadId());
				command->Execute();
				printf("[0x%08lx] <<< CommandManager ThreadHandlerProc: Executing command done \n", GetCurrentThreadId());
			}
			else
			{
				printf("[0x%08lx] >>> CommandManager ThreadHandlerProc: null item \n", GetCurrentThreadId());
			}
		}
		return 0;
	}
};


class CommandManager : public ThreadHandler, Thread
{
public:
	~CommandManager();
	virtual unsigned ThreadHandlerProc(void);
	static CommandManager* Instance();
	QueueManager<Command>* GetCommandList();
private:
	static CommandManager* m_Instance;
	CommandManager();
	QueueManager<Command>* m_CommandList;
private:

	struct JobInfo
	{
		bool Completed;
		CommandWorker* commandWorker;
	};

	std::vector<JobInfo*> m_ThreadList;
	long m_lWorkerThreadCount;
};

}