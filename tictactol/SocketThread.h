#pragma once

#include "SocketHandler.h"

template <class T>
class SocketThread: public bbg::Thread
{
public:
	SocketThread(SocketHandler<T>* handler);
	~SocketThread(void);
	static SocketThread* Create();
	//SocketHandler* GetProcHandler(void);

private:
	//SocketHandler* m_pHandler;
};

template <class T>
SocketThread<T>::SocketThread(SocketHandler<T>* handler):Thread(handler)
{
	//m_pHandler = handler;
}

template <class T>
SocketThread<T>::~SocketThread(void)
{

}

template <class T>
SocketThread<T>* SocketThread<T>::Create()
{
	SocketHandler<T>* m_pSocketHandler = new SocketHandler<T>();
	SocketThread<T>* t = new SocketThread<T>(m_pSocketHandler);
	return t;
}

//template <class T>
//SocketHandler<T>* SocketThread<T>::GetProcHandler(void)
//{
//	return m_pHandler;
//}