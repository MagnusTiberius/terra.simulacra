#include "CommandManager.h"

namespace bbg {

CommandManager* CommandManager::m_Instance = 0;

CommandManager::CommandManager(): Thread(this)
{
	printf("[0x%08lx] CommandManager CommandManager ctor: \n", GetCurrentThreadId());
	m_CommandList = QueueManager<Command>::Instance();
	m_lWorkerThreadCount = 0;
}


CommandManager::~CommandManager()
{
}

CommandManager* CommandManager::Instance() {
	if (m_Instance == 0) {
		m_Instance = new CommandManager();
	}
	return m_Instance;
}

unsigned CommandManager::ThreadHandlerProc(void)
{
	while (true)
	{
		if (m_lWorkerThreadCount < 80)
		{
			JobInfo* jobInfo = new JobInfo();
			jobInfo->Completed = false;
			jobInfo->commandWorker = new CommandWorker();
			printf("[0x%08lx] CommandManager ThreadHandlerProc Add Worker Thread #%d: \n", GetCurrentThreadId(), m_lWorkerThreadCount);
			m_ThreadList.push_back(jobInfo);
			m_lWorkerThreadCount++;
		}
	}
	return 0;
}

QueueManager<Command>* CommandManager::GetCommandList()
{
	return m_CommandList;
}

}