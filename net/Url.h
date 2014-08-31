#pragma once

#include <string>

namespace bbg {

class Url
{
public:
	Url(void);
	~Url(void);
public:
	void SetDomain(std::wstring v);
	std::wstring GetDomain();
	void SetPath(std::wstring v);
	std::wstring GetPath();
	void SetQueryString(std::wstring v);
	std::wstring GetQueryString();
	void SetPort(int v);
	int GetPort();
private:
	std::wstring m_Domain;
	std::wstring m_Path;
	std::wstring m_QueryString;
	int m_Port;
};

}



