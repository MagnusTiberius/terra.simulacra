#pragma once
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include "Url.h"
#include "Socket.h"
#include <vector>

namespace bbg {

class Connection
{
public:
	Connection(void);
	Connection(Url* url);
	~Connection(void);
	static Connection* Connect(std::wstring domain, int port);

	int Send(char* buffer);
	int Receive(char* buffer);
private:
	bbg::Socket* m_socket;
	Url* m_url;
	std::vector<char*> m_BufferList;
};

}
