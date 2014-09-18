#pragma once
#include "Thread.h"
#include "ThreadHandler.h"
#include "CircularQueue.h"
#include "Mutex.h"
#include "Event.h"
#include <string>
namespace bbg {
using namespace bbg;

template <class T>
class ChannelManager : public Thread, ThreadHandler
{
public:
	static ChannelManager* Instance(); //Singleton
	~ChannelManager();
	virtual unsigned ThreadHandlerProc(void);
private:
	ChannelManager(); //disable new 
	static ChannelManager* m_pInstance;
private:
	template <class T>
	class QueueManager
	{
	public:
		QueueManager() :m_mNowriters(), m_eHasItems(TRUE, TRUE) { }
		~QueueManager() { }
		void Write(T* p)
		{
			circularQueue.Write(p);
		}
		T* Read()
		{
			T* t = NULL;
			if (!circularQueue.IsEmpty())
				t = circularQueue.Read();
			else
				m_eNotEmpty.Reset();
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
		CircularQueue<T> circularQueue;
	private:
		Mutex m_mNowriters;
		Event m_eHasItems;
	};
protected:
	QueueManager<T> qManager;
public:
	T* Read()
	{
		qManager.GrantReaderAccess()
		T* t =	qManager.Read();
		qManager.ReleaseReaderAccess();
		return t;
	}
	void Write(T* p)
	{
		qManager.GrantWriterAccess()
		qManager.Write(p);
		qManager.ReleaseWriterAccess();
	}
};

//==========================

template <class T>
ChannelManager<T>* ChannelManager<T>::m_pInstance = 0;

template <class T>
ChannelManager<T>* ChannelManager<T>::Instance()
{
	if (m_pInstance == 0) {
		m_pInstance = new ChannelManager();
	}
	return m_pInstance;
}

template <class T>
ChannelManager<T>::ChannelManager() : Thread(this), ThreadHandler()
{
	Suspend();
}


template <class T>
ChannelManager<T>::~ChannelManager()
{
}

template <class T>
unsigned ChannelManager<T>::ThreadHandlerProc(void)
{
	return 0;
}



}