#pragma once

#include <string>
#include <map>

namespace bbg {

class RequestData
{
public:
	RequestData(void);
	~RequestData(void);
	void SetUserID(std::string v);
	std::string GetUserID();
	void SetMessageData(std::string v);
	std::string GetMessageData();
	void SetSocket(int v);
	int GetSocket();
private:
	static int SeqID;
	std::string m_UserID;
	std::string m_Message;
	int m_Socket;
};

}


