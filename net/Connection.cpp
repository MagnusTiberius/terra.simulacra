#include "Connection.h"

namespace bbg {

Connection::Connection(void)
{
	m_socket = new bbg::Socket(DEFAULT_DOMAIN, (int)DEFAULT_PORT);
}


Connection::~Connection(void)
{
	delete m_socket;
	delete m_url;
}

Connection::Connection(Url* url)
{
	m_url = url;
	m_socket = new bbg::Socket(url->GetDomain(), url->GetPort());
}


Connection* Connection::Connect(std::wstring domain, int port)
{
	Url* url = new Url();
	url->SetDomain(domain);
	url->SetPort(port);
	Connection* c = new Connection(url);
	return c;
}

int Connection::Send(char* buffer)
{
	return m_socket->Send(buffer);
}

int Connection::Receive(char* buffer)
{
	char* m_TempBuffer = (char*)malloc(sizeof(DEFAULT_BUFLEN));
	int n = m_socket->Receive(m_TempBuffer,DEFAULT_BUFLEN);
	if (n == 0 )
	{
		buffer = m_TempBuffer;
		return n;
	}
	m_BufferList.push_back(m_TempBuffer);
	do 
	{
		n = m_socket->Receive(m_TempBuffer,DEFAULT_BUFLEN);
		m_BufferList.push_back(_strdup(m_TempBuffer));
	} while (n > 0);
	return n;
}

}