#pragma once

#include <string>
#include <map>

class RequestData
{
public:
	RequestData(void);
	~RequestData(void);
	void SetUserID(std::string v);
	std::string GetUserID();
	void SetMessage(std::string v);
	std::string GetMessage();
private:
	static int SeqID;
	std::string m_UserID;
	std::string m_Message;
};



