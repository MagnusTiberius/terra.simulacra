#pragma once
#include "RequestData.h"
#include <vector>
#include "CircularBuffer.h"
#include "Mutex.h"
#include "Event.h"

namespace bbg {

template <class T>
class RequestDataManager
{
public:
	~RequestDataManager(void);
	static RequestDataManager* Instance();
	void AddRequestData(T* d);
	void ReadRequestData(T* d);
	void GrantReaderAccess();
	void ReleaseReaderAccess();
	void GrantWriterAccess();
	void ReleaseWriterAccess();
	void SetBufferSize(int size);
protected:
	bbg::CircularBuffer<T> m_RequestDataList;
	bbg::Mutex m_mNowriters;
	bbg::Event m_eNoreaders;
	int m_nReaderSize;
private:
	RequestDataManager(void);
	RequestDataManager(int size);
    static RequestDataManager* m_Instance;
};

template <class T>
RequestDataManager<T>* RequestDataManager<T>::m_Instance = 0;

template <class T>
RequestDataManager<T>* RequestDataManager<T>::Instance() {
    if (m_Instance == 0) {
        m_Instance = new RequestDataManager<T>();
    }
    return m_Instance;
}

template <class T>
RequestDataManager<T>::RequestDataManager(void)
	: m_mNowriters(), m_eNoreaders(TRUE,TRUE)
{
	m_nReaderSize=0;
	m_RequestDataList.Init(512);
}

template <class T>
RequestDataManager<T>::RequestDataManager(int size)
{
	m_RequestDataList.Init(size);
}

template <class T>
void RequestDataManager<T>::SetBufferSize(int size)
{
	m_RequestDataList.Init(size);
}

template <class T>
RequestDataManager<T>::~RequestDataManager(void)
{
}



template <class T>
void RequestDataManager<T>::AddRequestData(T* d)
{
	m_RequestDataList.Write(d);
}

template <class T>
void RequestDataManager<T>::ReadRequestData(T* d)
{
	if (!m_RequestDataList.IsEmpty())
		m_RequestDataList.Read(d);
}

template <class T>
void RequestDataManager<T>::GrantReaderAccess()
{
    m_mNowriters.Wait(INFINITE);
    m_nReaderSize++;
    m_eNoreaders.Reset();
    m_mNowriters.Release();
}

template <class T>
void RequestDataManager<T>::ReleaseReaderAccess()
{
    m_mNowriters.Wait(INFINITE);
    if (--m_nReaderSize == 0) 
	{
        m_eNoreaders.Set();
    }
    m_mNowriters.Release();
}

template <class T>
void RequestDataManager<T>::GrantWriterAccess()
{
	m_mNowriters.WaitForTwo( m_eNoreaders, TRUE, INFINITE);
}

template <class T>
void RequestDataManager<T>::ReleaseWriterAccess()
{
	m_mNowriters.Release();
}

}