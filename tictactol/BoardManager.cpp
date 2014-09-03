#include "BoardManager.h"

namespace bbg {

BoardManager* BoardManager::_instance = 0;

BoardManager::BoardManager(void)
{
}


BoardManager::~BoardManager(void)
{
}

BoardManager* BoardManager::Instance() {
    if (_instance == 0) {
        _instance = new BoardManager;
    }
    return _instance;
}

void BoardManager::AddBoard(Board* board)
{
	m_BoardList.push_back(board);
}

void BoardManager::Init(void)
{
	for (int i=0; i<20; i++)
	{
		AddBoard(new Board());
	}
}

void BoardManager::Join(User* user, Board* board)
{
	board->JoinBoard(user);
}

void BoardManager::Leave(User* user, Board* board)
{
	board->LeaveBoard(user);
}

void BoardManager::Create(User* user)
{
	m_UserList.insert(std::pair<std::string, User*>(user->GetLoginId(),user));
}

}