#include "User.h"

namespace bbg {

User::User(void)
{
	char* userid = (char*)malloc(10);
	//m_LoginId = Util::Token(strlen(userid));
	Util::GenerateRandomChars(userid, strlen(userid));
	m_LoginId = userid;
}

User::~User(void)
{
}

void User::SetLoginId(std::string v)
{
	m_LoginId = std::string(v);
}


std::string User::GetLoginId(void)
{
	return m_LoginId;
}

}