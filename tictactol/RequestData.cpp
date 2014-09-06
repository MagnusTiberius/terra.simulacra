#include "RequestData.h"

namespace bbg {

int RequestData::SeqID = 0;

RequestData::RequestData(void)
{
	SeqID++;
	m_Message = "";
	m_UserID = "";
}

RequestData::~RequestData(void)
{
}

void RequestData::SetUserID(std::string v)
{
	m_UserID = v;
}

std::string RequestData::GetUserID()
{
	return m_UserID;
}

void RequestData::SetMessageData(std::string v)
{
	m_Message = v;
}

std::string RequestData::GetMessageData()
{
	return m_Message;
}

void RequestData::SetSocket(int v)
{
	m_Socket = v;
}

int RequestData::GetSocket()
{
	return m_Socket;
}

}