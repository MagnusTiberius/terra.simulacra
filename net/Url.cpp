#include "Url.h"

namespace bbg {

Url::Url(void)
{
}


Url::~Url(void)
{
}

void Url::SetDomain(std::wstring v)
{
	m_Domain = v;
}

std::wstring Url::GetDomain()
{
	return m_Domain;
}

void Url::SetPath(std::wstring v)
{
	m_Path = v;
}

std::wstring Url::GetPath()
{
	return m_Path;
}

void Url::SetQueryString(std::wstring v)
{
	m_QueryString = v;
}

std::wstring Url::GetQueryString()
{
	return m_QueryString;
}

void Url::SetPort(int v)
{
	m_Port = v;
}

int Url::GetPort()
{
	return m_Port;
}

}