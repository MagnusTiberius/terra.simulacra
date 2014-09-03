#pragma once

#include <vector>

class ClientXm
{
public:
	ClientXm(SOCKET s);
	~ClientXm(void);
protected:
	SOCKET m_Socket;
	std::vector<char*> m_BufferList;
};

