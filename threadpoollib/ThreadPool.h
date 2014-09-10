#pragma once
#include "Thread.h"
#include "ThreadHandler.h"
#include <vector>

#define MIN_WORKER 2
#define MAX_WORKER 5
#define TIMEOUT 60000

using namespace bbg;

namespace bbg{

class ThreadPool : public ThreadHandler
{
public:
	ThreadPool(void);
	~ThreadPool(void);
private:
	long m_nMinWorker;
	long m_nMaxWorker;
	DWORD m_dTimeOut;
	virtual unsigned ThreadHandlerProc(void);
	void InitPool(void);
	long m_lCurrWorkerCount;
	std::vector<Thread*> m_pThreadWorkerList;
};

}

