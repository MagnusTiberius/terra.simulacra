#include "ThreadPool.h"

namespace bbg{

ThreadPool::ThreadPool(void)
{
	m_nMinWorker = MIN_WORKER;
	m_nMaxWorker = MAX_WORKER;
	m_dTimeOut = TIMEOUT;
	m_lCurrWorkerCount = 0;
	m_bRunning = true;
	m_pTaskList = QueueManager<DispatchHandler>::Instance();
	InitPool();
}


ThreadPool::~ThreadPool(void)
{
	m_ThreadList.TerminateAllThreads();
}

unsigned ThreadPool::ThreadHandlerProc(void)
{
	while(true)
	{
		printf("[0x%08lx] ThreadPool::ThreadHandlerProc have a job to do\n", GetCurrentThreadId());
		DispatchHandler* task;
		m_pTaskList->GrantWriterAccess();
		task = m_pTaskList->ReadRequestData();
		m_pTaskList->ReleaseWriterAccess();
		if (task != NULL)
		{
			task->Execute();
		}
	}
	return 0;
}

void ThreadPool::InitPool(void)
{
	while(m_lCurrWorkerCount < m_nMinWorker)
	{
		Thread* thread = new Thread(this, CREATE_SUSPENDED);
		if (thread)
		{
			DWORD dwThreadId = thread->GetThreadId2();
			m_ThreadList.AddThread(dwThreadId, thread);
		}
		m_lCurrWorkerCount++;
	}
}

bool ThreadPool::DispatchThread(ThreadHandler* handler)
{
	DispatchHandler* task = new DispatchHandler(handler);
	m_pTaskList->GrantWriterAccess();
	m_pTaskList->AddRequestData(task);
	m_pTaskList->ReleaseWriterAccess();
	return true;
}

bool ThreadPool::IsRunning()
{
	return m_bRunning;
}

void ThreadPool::Shutdown()
{
	m_bRunning = false;
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
	threadInfo->thread = thread;
	threadInfo->threadId = dwThreadId;
	AddThread(dwThreadId, threadInfo);
	thread->Resume();
}

void ThreadPool::ThreadList::AddThread(DWORD dwThreadId, THREADITEMINFO *threadInfo)
{
	m_mList.insert(std::pair<DWORD, THREADITEMINFO*>(dwThreadId,threadInfo));
}

void ThreadPool::ThreadList::RemoveThread(DWORD dwThreadId)
{
	std::map<DWORD, THREADITEMINFO*>::iterator itr;
	itr = m_mList.find(dwThreadId);
	m_mList.erase(itr);
}

void ThreadPool::ThreadList::TerminateAllThreads()
{
	for(std::pair<DWORD, THREADITEMINFO*> t: m_mList)
	{
		THREADITEMINFO* info = t.second;
		info->thread->Terminate(1);
		delete info->thread;
		info->thread = NULL;
		info->threadId = 0;
		memset(info, 0, sizeof(THREADITEMINFO));
		delete info;
	}
	m_mList.clear();
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