#pragma once
#include "RequestData.h"
#include <vector>
#include "CircularBuffer.h"
#include "Mutex.h"
#include "Event.h"
#include "Thread.h"
#include "DataManager.h"
#include "ThreadHandler.h"
#include "SocketClient.h"
#include "Singleton.h"




namespace bbg {



template <class T>
class SocketManager
{
public:
	~SocketManager(void);
	static SocketManager* Instance();
	ReadDataManager* GetReadBuffer();
	WriteDataManager* GetWriteBuffer();
private:
	ReadDataManager* readBuffer;
	WriteDataManager* writeBuffer;
	static SocketManager* m_Instance;
	SocketManager(void);
public:
	void OutBufferWrite(RequestData* d);
	//void OutBufferRead(RequestData* d);
	void InBufferWrite(RequestData* d);
	void InBufferRead(RequestData* d);
	RequestData* OutBufferRead();
};

template <class T>
SocketManager<T>* SocketManager<T>::m_Instance = 0;

template <class T>
SocketManager<T>* SocketManager<T>::Instance() {
    if (m_Instance == 0) {
        m_Instance = new SocketManager<T>();
    }
    return m_Instance;
}

template <class T>
SocketManager<T>::SocketManager(void) 
{
	readBuffer = bbg::DataManager<T*>::Instance();
	readBuffer->SetBufferSize(1024*4);
	writeBuffer = DataManager<T*>::Instance();
	writeBuffer->SetBufferSize(1024*4);
}

template <class T>
SocketManager<T>::~SocketManager(void)
{
}

template <class T>
ReadDataManager* SocketManager<T>::GetReadBuffer()
{
	return readBuffer;
}

template <class T>
ReadDataManager* SocketManager<T>::GetWriteBuffer()
{
	return writeBuffer;
}


template <class T>
void SocketManager<T>::OutBufferWrite(RequestData* d)
{
	writeBuffer->GrantWriterAccessEx();
	writeBuffer->AddRequestData(d);
	writeBuffer->ReleaseWriterAccessEx();
}

template <class T>
RequestData* SocketManager<T>::OutBufferRead()
{
	RequestData* d = NULL;
	writeBuffer->GrantReaderAccessEx();
	d = writeBuffer->ReadRequestData();
	writeBuffer->ReleaseReaderAccessEx();
	return d;
}

template <class T>
void SocketManager<T>::InBufferWrite(RequestData* d)
{
	readBuffer->GrantWriterAccessEx();
	readBuffer->AddRequestData(d);
	readBuffer->ReleaseWriterAccessEx();
}

template <class T>
void SocketManager<T>::InBufferRead(RequestData* d)
{
	readBuffer->GrantReaderAccessEx();
	readBuffer->ReadRequestData(d);
	readBuffer->ReleaseReaderAccessEx();
	return;
}





}