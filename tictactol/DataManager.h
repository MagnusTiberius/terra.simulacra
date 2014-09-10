#pragma once
#include "RequestData.h"
#include <vector>
#include "CircularBuffer.h"
#include "Mutex.h"
#include "Event.h"


namespace bbg {

template <class T>
class DataManager
{
public:
	~DataManager(void);
	DataManager(void);
	static DataManager* Instance();
	void AddRequestData(RequestData* d);
	void ReadRequestData(RequestData* d);
	void GrantReaderAccess();
	void ReleaseReaderAccess();
	void GrantWriterAccess();
	void ReleaseWriterAccess();
	void SetBufferSize(int size);
	bbg::CircularBuffer<RequestData>* GetBuffer();
protected:
	bbg::CircularBuffer<RequestData> m_RequestDataList;
	bbg::Mutex m_mNowriters;
	bbg::Event m_eNoreaders;
	bbg::Event m_eNotEmpty;
	int m_nReaderSize;
private:
	DataManager(int size);
    static DataManager* m_Instance;
};

template <class T>
DataManager<T>* DataManager<T>::m_Instance = 0;

template <class T>
DataManager<T>* DataManager<T>::Instance() {
    if (m_Instance == 0) {
        m_Instance = new DataManager<T>();
    }
    return m_Instance;
}

template <class T>
DataManager<T>::DataManager(void)
	: m_mNowriters(), m_eNoreaders(TRUE,TRUE), m_eNotEmpty(TRUE,TRUE)
{
	m_nReaderSize=0;
	m_RequestDataList.Init(512);
}

template <class T>
DataManager<T>::DataManager(int size)
{
	m_RequestDataList.Init(size);
}

template <class T>
void DataManager<T>::SetBufferSize(int size)
{
	m_RequestDataList.Init(size);
}

template <class T>
DataManager<T>::~DataManager(void)
{
}

template <class T>
bbg::CircularBuffer<RequestData>* DataManager<T>::GetBuffer()
{
	return m_RequestDataList;
}

template <class T>
void DataManager<T>::AddRequestData(RequestData* d)
{
	m_RequestDataList.Write(d);
	if (!m_RequestDataList.IsEmpty())
		m_eNotEmpty.Set();
}

template <class T>
void DataManager<T>::ReadRequestData(RequestData* d)
{
	if (!m_RequestDataList.IsEmpty())
	{
		m_RequestDataList.Read(d);
	}
	else
	{
		m_eNotEmpty.Reset();
	}
}

template <class T>
void DataManager<T>::GrantReaderAccess()
{
	//m_eNotEmpty.Wait(INFINITE);
    m_mNowriters.Wait(INFINITE);
    m_nReaderSize++;
    m_eNoreaders.Reset();
    m_mNowriters.Release();
}

template <class T>
void DataManager<T>::ReleaseReaderAccess()
{
    m_mNowriters.Wait(INFINITE);
    if (--m_nReaderSize == 0) 
	{
        m_eNoreaders.Set();
    }
    m_mNowriters.Release();
}

template <class T>
void DataManager<T>::GrantWriterAccess()
{
	//m_eNotEmpty.Wait(INFINITE);
	m_mNowriters.WaitForTwo( m_eNoreaders, TRUE, INFINITE);
}

template <class T>
void DataManager<T>::ReleaseWriterAccess()
{
	m_mNowriters.Release();
}


typedef bbg::DataManager<bbg::RequestData*> ReadDataManager;
typedef bbg::DataManager<bbg::RequestData*> WriteDataManager;

}