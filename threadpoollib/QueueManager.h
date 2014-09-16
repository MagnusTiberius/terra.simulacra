#pragma once
#include "RequestData.h"
#include <vector>
#include "CircularQueue.h"
#include "Mutex.h"
#include "Event.h"

namespace bbg {

template <class T>
class QueueManager
{
public:
	~QueueManager(void);
	static QueueManager* Instance();
	void AddRequestData(T* d);
	T* ReadRequestData();
	void GrantReaderAccess();
	void ReleaseReaderAccess();
	void GrantReaderAccessEx();
	void ReleaseReaderAccessEx();
	void GrantWriterAccess();
	void ReleaseWriterAccess();
	void GrantWriterAccessEx();
	void ReleaseWriterAccessEx();
	void SetBufferSize(int size);
	int Size(void);
protected:
	bbg::CircularQueue<T> m_RequestDataList;
	bbg::Mutex m_mNowriters;
	bbg::Event m_eNoreaders;
	bbg::Event m_eNoItems;
	bbg::Event m_eHasItems;
	int m_nReaderSize;
private:
	QueueManager(void);
	QueueManager(int size);
    static QueueManager* m_Instance;
};

template <class T>
QueueManager<T>* QueueManager<T>::m_Instance = 0;

template <class T>
QueueManager<T>* QueueManager<T>::Instance(void) {
    if (m_Instance == 0) {
        m_Instance = new QueueManager<T>();
    }
    return m_Instance;
}

template <class T>
QueueManager<T>::QueueManager(void)
	: m_mNowriters(), m_eNoreaders(TRUE, TRUE), m_eNoItems(TRUE, TRUE), m_eHasItems(TRUE, TRUE)
{
	m_nReaderSize=0;
}

template <class T>
QueueManager<T>::QueueManager(int size)
{
	m_RequestDataList.Init(size);
}

template <class T>
void QueueManager<T>::SetBufferSize(int size)
{
	//m_RequestDataList.Init(size);
}

template <class T>
QueueManager<T>::~QueueManager(void)
{
}

template <class T>
void QueueManager<T>::AddRequestData(T* d)
{
	m_RequestDataList.Write(d);
}

template <class T>
T* QueueManager<T>::ReadRequestData()
{
	if (!m_RequestDataList.IsEmpty())
		return m_RequestDataList.Read();
	return NULL;
}

template <class T>
void QueueManager<T>::GrantReaderAccess()
{
    m_mNowriters.Wait(INFINITE);
    m_nReaderSize++;
    m_eNoreaders.Reset();
    m_mNowriters.Release();
}

template <class T>
void QueueManager<T>::ReleaseReaderAccess()
{
    m_mNowriters.Wait(INFINITE);
    if (--m_nReaderSize == 0) 
	{
        m_eNoreaders.Set();
    }
    m_mNowriters.Release();
}

template <class T>
void QueueManager<T>::GrantReaderAccessEx()
{
	m_mNowriters.WaitForTwo(m_eHasItems, TRUE, INFINITE);
}

template <class T>
void QueueManager<T>::ReleaseReaderAccessEx()
{
	m_mNowriters.Release();
	if (m_RequestDataList.Size() == 0) 
		m_eHasItems.Reset();
}


template <class T>
void QueueManager<T>::GrantWriterAccess()
{
	m_mNowriters.WaitForTwo( m_eNoreaders, TRUE, INFINITE);
}

template <class T>
void QueueManager<T>::ReleaseWriterAccess()
{
	m_mNowriters.Release();
}

template <class T>
void QueueManager<T>::GrantWriterAccessEx()
{
	m_mNowriters.Wait(INFINITE);
}

template <class T>
void QueueManager<T>::ReleaseWriterAccessEx()
{
	m_mNowriters.Release();
	m_eHasItems.Set();
}


template <class T>
int QueueManager<T>::Size(void)
{
	return m_RequestDataList.Size();
}


}