#pragma once
#include "Thread.h"
#include "ThreadHandler.h"
#include <vector>
#include <map>
#include "QueueManager.h"

#define MIN_WORKER 2
#define MAX_WORKER 5000
#define TIMEOUT 60000

using namespace bbg;

namespace bbg{

class ThreadPool : public ThreadHandler
{
public:
	ThreadPool(void);
	~ThreadPool(void);
public:
	bool IsRunning();
	void Shutdown();
	void SetTaskComplete(DWORD threadId);
	void SetTaskStart(DWORD threadId);
	void AddWorkerThread(void);
	bool AllJobsCompleted();
private:
	long m_nMinWorker;
	long m_nMaxWorker;
	DWORD m_dTimeOut;
	virtual unsigned ThreadHandlerProc(void);
	void InitPool(void);
	long m_lCurrWorkerCount;
	bool m_bRunning;
	long m_nThreadsStarted;
	bool m_bShuttingDown;
	Event m_eShutdownOK;

private:
	class ThreadList
	{
	public:
		ThreadList(void);
		~ThreadList(void);
	private:
		struct THREADITEMINFO
		{
			bool bDone;
			bool bFreeSlot;
			DWORD threadId;
			Thread *thread;
			long lFrequency;
		};
		std::map<DWORD, THREADITEMINFO*> m_mList;
	public:
		void AddThread(DWORD dwThreadId, Thread *thread);
		void AddThread(DWORD dwThreadId, THREADITEMINFO *threadInfo);
		void RemoveThread(DWORD dwThreadId);
		void TerminateAllThreads();
		void GrantWriterAccess();
		void ReleaseWriterAccess();
		void GrantReaderAccess();
		void ReleaseReaderAccess();
		THREADITEMINFO * GetThreadInfo(DWORD dwThreadId);
		int Size();
	private:
		Mutex m_mNowriters;
		Event m_eNoreaders;
		int m_nReaderSize;
	};

private:
	class DispatchHandler
	{
	public:
		DispatchHandler(void);
		DispatchHandler(ThreadHandler* handler);
		~DispatchHandler(void);
		int Execute(void);
	private:
		ThreadHandler* m_phandler;
	};

public:
	bool DispatchThread(ThreadHandler* handler);
	int GetThreadListSize();

private:
	ThreadList m_ThreadList;
	QueueManager<DispatchHandler>* m_pTaskList;
};

}

