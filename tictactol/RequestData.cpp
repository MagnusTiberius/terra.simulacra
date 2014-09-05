#include "RequestData.h"


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

void RequestData::SetMessage(std::string v)
{
	m_Message = v;
}

std::string RequestData::GetMessage()
{
	return m_Message;
}