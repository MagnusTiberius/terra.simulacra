#include "ThreadPool.h"

namespace bbg{

ThreadPool::ThreadPool(void)
{
	m_nMinWorker = MIN_WORKER;
	m_nMaxWorker = MAX_WORKER;
	m_dTimeOut = TIMEOUT;
	m_lCurrWorkerCount = 0;
	InitPool();
}


ThreadPool::~ThreadPool(void)
{
}

unsigned ThreadPool::ThreadHandlerProc(void)
{
	return 0;
}

void ThreadPool::InitPool(void)
{
	while(m_lCurrWorkerCount < m_nMinWorker)
	{
		Thread* thread = new Thread(this, CREATE_SUSPENDED);
		if (thread)
		{
			m_pThreadWorkerList.push_back(thread);
		}
		m_lCurrWorkerCount++;
	}
}


}