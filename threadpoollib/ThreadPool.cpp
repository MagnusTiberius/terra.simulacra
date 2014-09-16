#include "ThreadPool.h"

namespace bbg{

ThreadPool::ThreadPool(void) :
	m_eShutdownOK(TRUE, TRUE)
{
	m_nMinWorker = MIN_WORKER;
	m_nMaxWorker = MAX_WORKER;
	m_dTimeOut = TIMEOUT;
	m_lCurrWorkerCount = 0;
	m_bRunning = true;
	m_nThreadsStarted = 0;
	m_bShuttingDown = false;
	m_pTaskList = QueueManager<DispatchHandler>::Instance();
	InitPool();
	m_eShutdownOK.Reset();
}


ThreadPool::~ThreadPool(void)
{
	m_eShutdownOK.Wait(INFINITE);
	m_ThreadList.TerminateAllThreads();
}

unsigned ThreadPool::ThreadHandlerProc(void)
{
	while(true)
	{
		printf("[0x%08lx] ThreadPool::ThreadHandlerProc have a job to do\n", GetCurrentThreadId());
		DispatchHandler* task;
		m_pTaskList->GrantReaderAccessEx();
		task = m_pTaskList->ReadRequestData();
		m_pTaskList->ReleaseReaderAccessEx();
		if (task != NULL)
		{
			SetTaskStart(GetCurrentThreadId());
			task->Execute();
			SetTaskComplete(GetCurrentThreadId());
		}
		if (AllJobsCompleted() && m_bShuttingDown && m_nThreadsStarted == 0)
		{
			m_bRunning = false;
			m_eShutdownOK.Set();
		}
	}
	return 0;
}

bool ThreadPool::AllJobsCompleted()
{
	bool b = false;
	if (m_pTaskList->Size() == 0)
	{
		b = true;
	}
	return b;
}

void ThreadPool::InitPool(void)
{
	while(m_lCurrWorkerCount < m_nMinWorker)
	{
		AddWorkerThread();
	}
}

void ThreadPool::AddWorkerThread(void)
{
	printf("Adding worker thread.\n");
	Thread* thread = new Thread(this, CREATE_SUSPENDED);
	if (thread)
	{
		DWORD dwThreadId = thread->GetThreadId2();
		m_ThreadList.AddThread(dwThreadId, thread);
	}
	m_lCurrWorkerCount++;
}

bool ThreadPool::DispatchThread(ThreadHandler* handler)
{
	if (!m_bShuttingDown)
	{
		if (m_nThreadsStarted >= m_lCurrWorkerCount && m_lCurrWorkerCount < m_nMaxWorker)
		{
			AddWorkerThread();
		}
		printf("[0x%08lx] Adding a task/job. \n", GetCurrentThreadId());
		DispatchHandler* task = new DispatchHandler(handler);
		m_pTaskList->GrantWriterAccessEx();
		m_pTaskList->AddRequestData(task);
		m_pTaskList->ReleaseWriterAccessEx();
		return true;
	}
	else
	{
		printf("[0x%08lx] Server is shutting down, cannot add additional jobs. \n", GetCurrentThreadId());
		return false;
	}
}

bool ThreadPool::IsRunning()
{
	return m_bRunning;
}

void ThreadPool::Shutdown()
{
	printf("[0x%08lx] Shutdown event signalled. \n", GetCurrentThreadId());
	m_bShuttingDown = true;
}

void ThreadPool::SetTaskComplete(DWORD threadId)
{
	auto threadInfo = m_ThreadList.GetThreadInfo(threadId);
	threadInfo->bDone = true;
	printf("[0x%08lx] TaskComplete\n", GetCurrentThreadId());
	m_nThreadsStarted--;
	threadInfo->lFrequency++;
}

void ThreadPool::SetTaskStart(DWORD threadId)
{
	auto threadInfo = m_ThreadList.GetThreadInfo(threadId);
	threadInfo->bDone = false;
	printf("[0x%08lx] TaskStart\n", GetCurrentThreadId());
	m_nThreadsStarted++;
}

// =============================================================================
//
//
// =============================================================================
ThreadPool::ThreadList::ThreadList(void)
	: m_mNowriters(), m_eNoreaders(TRUE,TRUE), m_nReaderSize(0)
{

}

ThreadPool::ThreadList::~ThreadList(void)
{

}

void ThreadPool::ThreadList::AddThread(DWORD dwThreadId, Thread *thread)
{
	THREADITEMINFO *threadInfo = new THREADITEMINFO();
	threadInfo->lFrequency = 0;
	threadInfo->thread = thread;
	threadInfo->threadId = dwThreadId;
	AddThread(dwThreadId, threadInfo);
	thread->Resume();
}

void ThreadPool::ThreadList::AddThread(DWORD dwThreadId, THREADITEMINFO *threadInfo)
{
	m_mList.insert(std::pair<DWORD, THREADITEMINFO*>(dwThreadId,threadInfo));
	threadInfo->bFreeSlot = false;
}

void ThreadPool::ThreadList::RemoveThread(DWORD dwThreadId)
{
	std::map<DWORD, THREADITEMINFO*>::iterator itr;
	itr = m_mList.find(dwThreadId);
	THREADITEMINFO *threadInfo = itr->second;
	threadInfo->thread->Terminate(0);
	delete threadInfo->thread;
	threadInfo->threadId = 0;
	m_mList.erase(itr);
	threadInfo->bFreeSlot = true;
}

void ThreadPool::ThreadList::TerminateAllThreads()
{
	int n = 1;
	int nTotalJobs = 0;
	for(std::pair<DWORD, THREADITEMINFO*> t: m_mList)
	{
		THREADITEMINFO* info = t.second;
		info->thread->Terminate(1);
		printf("#%d Worker Thread removed [ID=0x%08lx], freq=%d\n", n, (DWORD)info->threadId, info->lFrequency);
		nTotalJobs+=info->lFrequency;
		delete info->thread;
		info->thread = NULL;
		info->threadId = 0;
		memset(info, 0, sizeof(THREADITEMINFO));
		delete info;
		n++;
	}
	printf("Total jobs: %d\n",nTotalJobs);
	m_mList.clear();
	::Sleep(8000);
}

void ThreadPool::ThreadList::GrantWriterAccess()
{
	m_mNowriters.WaitForTwo( m_eNoreaders, TRUE, INFINITE);
}

void ThreadPool::ThreadList::ReleaseWriterAccess()
{
	m_mNowriters.Release();
}

void ThreadPool::ThreadList::GrantReaderAccess()
{
    m_mNowriters.Wait(INFINITE);
    m_nReaderSize++;
    m_eNoreaders.Reset();
    m_mNowriters.Release();
}

void ThreadPool::ThreadList::ReleaseReaderAccess()
{
    m_mNowriters.Wait(INFINITE);
    if (--m_nReaderSize == 0) 
	{
        m_eNoreaders.Set();
    }
    m_mNowriters.Release();
}

ThreadPool::ThreadList::THREADITEMINFO* ThreadPool::ThreadList::GetThreadInfo(DWORD dwThreadId)
{
	std::map<DWORD, THREADITEMINFO*>::iterator itr;
	itr = m_mList.find(dwThreadId);
	THREADITEMINFO* threadinfo = itr->second;
	return threadinfo;
}
// =============================================================================
//
//
// =============================================================================
ThreadPool::DispatchHandler::DispatchHandler(void)
{
	m_phandler = 0;
}

ThreadPool::DispatchHandler::DispatchHandler(ThreadHandler* handler)
{
	m_phandler = handler;
}

ThreadPool::DispatchHandler::~DispatchHandler(void)
{

}

int ThreadPool::DispatchHandler::Execute(void)
{
	int retval = 0;
	if (m_phandler)
	{
		retval = m_phandler->ThreadHandlerProc();
	}
	return retval;
}

// =============================================================================
//
//
// =============================================================================

}