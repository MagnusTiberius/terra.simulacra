#include "Board.h"

namespace bbg {

Board::Board(void)
{
	m_Id = Util::CreateGuid();
}


Board::~Board(void)
{
}

std::wstring Board::GetId(void)
{
	return m_Id;
}

void Board::JoinBoard(User* v)
{
	m_UserList.insert(std::pair<std::string, User*>(v->GetLoginId(),v));
}

void Board::LeaveBoard(User* v)
{
	m_UserList.erase(m_UserList.find(v->GetLoginId()));
}

}