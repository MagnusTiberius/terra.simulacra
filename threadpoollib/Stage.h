#pragma once
#include "Thread.h"
#include "ThreadHandler.h"
#include "CircularQueue.h"
#include "Mutex.h"
#include "Event.h"
#include "Command.h"
#include <string>
#include <map>
#define DEFAULT_WORKER_THREAD_SZ 2
namespace bbg {
using namespace bbg;

template <class T>
class Stage : public Thread, ThreadHandler
{
public:
	static Stage* Instance(); //Singleton summa optime est
	~Stage();
	virtual unsigned ThreadHandlerProc(void);
	int AvailableWorkerCount(void);
private:
	Stage(); //non optime new 
	static Stage* m_pInstance;
protected:
	template <class T>
	class Job
	{
	public:
		Job() :m_mNowriters(), m_eHasItems(TRUE, TRUE) { }
		~Job() { }
		void Write(ICommand* p)
		{
			circularQueue.Write(p);
		}
		ICommand* Read()
		{
			T* t = NULL;
			if (!circularQueue.IsEmpty())
				t = circularQueue.Read();
			else
				m_eHasItems.Reset();
			return t;
		}
		void GrantReaderAccess()
		{
			m_mNowriters.WaitForTwo(m_eHasItems, TRUE, INFINITE);
		}
		void ReleaseReaderAccess()
		{
			m_mNowriters.Release();
			if (circularQueue.Size() == 0)
				m_eHasItems.Reset();
		}
		void GrantWriterAccess()
		{
			m_mNowriters.Wait(INFINITE);
		}
		void ReleaseWriterAccess()
		{
			m_mNowriters.Release();
			m_eHasItems.Set();
		}
	private:
		CircularQueue<ICommand> circularQueue;
	private:
		Mutex m_mNowriters;
		Event m_eHasItems;
	};
protected:
	Job<ICommand> m_spJobList;
protected:
	class Worker : public Thread, ThreadHandler
	{
	public:
		Worker(Job<ICommand>* p) : Thread(this, CREATE_SUSPENDED), ThreadHandler() { m_JobList = p; }
		~Worker() {}
		virtual unsigned ThreadHandlerProc(void)
		{
			while (true)
			{
				//printf("Getting a job from queue.\n ");
				m_JobList->GrantReaderAccess();
				ICommand* job = m_JobList->Read();
				m_JobList->ReleaseReaderAccess();
				m_bIsAvailable = false;
				if (job != NULL)
				{
					//printf("Executing job. \n");
					job->Execute();
					//printf("Done. \n");
				}
				m_bIsAvailable = true;
				//printf("\n");
			}
			return 0;
		}
		bool IsAvailable(void)
		{
			return m_bIsAvailable;
		}
	private:
		bool m_bIsAvailable;
		Job<ICommand>* m_JobList;
	};
public:
	void Write(T* p)
	{
		m_spJobList.GrantWriterAccess()
		m_spJobList.Write(p);
		m_spJobList.ReleaseWriterAccess();
	}
private:
	std::map<DWORD, Worker*> m_pWorkerThreadList;
	int m_iAvailableWorkerCount;
};

//==========================

template <class T>
Stage<T>* Stage<T>::m_pInstance = 0;

template <class T>
Stage<T>* Stage<T>::Instance()
{
	if (m_pInstance == 0) {
		m_pInstance = new Stage();
	}
	return m_pInstance;
}

template <class T>
Stage<T>::Stage() : Thread(this, CREATE_SUSPENDED), ThreadHandler()
{
	for (int i = 0; i < DEFAULT_WORKER_THREAD_SZ; i++)
	{
		Worker* worker = new Worker(&m_spJobList);
		DWORD threadId = worker->GetThreadId2();
		m_pWorkerThreadList.insert(std::pair<DWORD, Worker*>(threadId, worker));
		worker->Resume();
	}
}

template <class T>
int Stage<T>::AvailableWorkerCount(void)
{
	m_iAvailableWorkerCount = 0;
	for (auto item : m_pWorkerThreadList)
	{
		Worker* obj = (Worker*)item.second;
		if (item->IsAvailable())
			m_iAvailableWorkerCount++;
	}
	return m_iAvailableWorkerCount;
}

template <class T>
Stage<T>::~Stage()
{
}

template <class T>
unsigned Stage<T>::ThreadHandlerProc(void)
{
	return 0;
}



}