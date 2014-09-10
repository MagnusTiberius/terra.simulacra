#pragma once
#include "SocketClient.h"
#include "ThreadHandler.h"

template <class T>
class SocketHandler: public bbg::ThreadHandler
{
public:
	SocketHandler(void);
	~SocketHandler(void);
	virtual unsigned ThreadHandlerProc(void);
private:
	bbg::SocketClient* socketClient;
	int iResult;
	char* buf;
};

template <class T>
SocketHandler<T>::SocketHandler(void)
{
	socketClient = new bbg::SocketClient(DEFAULT_DOMAIN, (int)DEFAULT_PORT);
}

template <class T>
SocketHandler<T>::~SocketHandler(void)
{

}

template <class T>
unsigned SocketHandler<T>::ThreadHandlerProc(void)
{
	bbg::SocketManager<RequestData>* sm = bbg::SocketManager<RequestData>::Instance();
	int nCtr = 0;
	while (true)
	{
		bbg::RequestData* d = new bbg::RequestData();
		d->SetMessageData("#*#");
		sm->OutBufferRead(d);
		if (d->GetMessageData().compare("#*#")!=0)
		{
			printf("Sending to server: %s %d\n", d->GetMessageData().c_str(),nCtr++);
			buf = const_cast<char*>(d->GetMessageData().c_str());
			char* b = const_cast<char*>(d->GetMessageData().c_str());
			std::string c = d->GetMessageData();
			const char* e = c.c_str();
			iResult = socketClient->Send(const_cast<char*>(e));
		}
	}
}