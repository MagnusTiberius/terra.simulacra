#pragma once
#include <string>
#include <ShlObj.h>
#include <algorithm>
#include <vector>

#include "Board.h"
#include "User.h"

namespace bbg {

class BoardManager
{
public:
	static BoardManager* Instance();
	void AddBoard(Board* v);
	void Init(void);
	void Join(User* u, Board* b);
	void Leave(User* u, Board* b);
	void Create(User* u);
protected:
	BoardManager(void);
	~BoardManager(void);
private:
    static BoardManager* _instance;
protected:
	std::vector<Board*> m_BoardList;
	std::map<std::string, User*> m_UserList;
};


}